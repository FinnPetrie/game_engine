#version 330 core

#define AMBIENT_OCCLUSION_COLOR_DELTA vec3(0.7)
#define GLOW false
#define AMBIENT_OCCLUSION_STRENGTH 0.008
#define FOG false

const int MAX_MARCHING_STEPS = 400;
const float MIN_DIST = 0.0;
const float MAX_DIST = 1000.0;
const float EPSILON = 0.00001;
const float Iterations = 15;
const vec4 background = vec4(0, 0, 0, 0);
const vec4 co = vec4(1, 1, 1, 0);
in vec3 vPos;
in vec3 vNormal;
in vec3 eyeDir;
in vec3 eyeRes;

out vec4 fragColour;


uniform vec2 screenSize;

//camera not functioning properly - space directions seem to change
uniform vec3 cameraCentre;
uniform vec3 cameraUp;
uniform mat4 view;
uniform vec4 eye;

struct Light{
    vec3 pos;
    vec4 colour;
};


uniform Light lights[10];
uniform int numLights;
uniform vec3 objectColour;

const vec4 lightPos = vec4(4.0, 8.0, -6.0, 1.0);
const vec4 lightColour = vec4(0.3, 0.5, 0.6, 1.0);

float intersectSDF(float distA, float distB){
    return max(distA, distB);
}

vec4 hProduct(vec4 q1, vec4 q2){
    vec4 r;
    r.x = q1.x*q2.x - dot( q1.yzw, q2.yzw );
    r.yzw = q1.x*q2.yzw + q2.x*q1.yzw + cross( q1.yzw, q2.yzw );
    return r;
    
}

vec4 quatSq( vec4 q )
{
    vec4 r;
    r.x = q.x*q.x - dot( q.yzw, q.yzw );
    r.yzw = 2*q.x*q.yzw;
    return r;
}

float unionSDF(float distA, float distB){
    return min(distA, distB);
}

float differenceSDF(float distA, float distB){
    return max(distA, -distB);
}

float sphereSDF(vec3 p, vec3 c, float radius){
    p.xyz = mod(p.xyz, 1.0) - c;
    return length(p) - radius;
}

float juliaMap( in vec3 p, out vec4 oTrap, in vec4 c )
{
    vec4 z = vec4(p,0.0);
    float md2 = 1.0;
    float mz2 = dot(z,z);

    vec4 trap = vec4(abs(z.xyz),dot(z,z));

    float n = 1.0;
    for( int i=0; i<Iterations; i++ )
    {
        // dz -> 2·z·dz, meaning |dz| -> 2·|z|·|dz|
        // Now we take thr 2.0 out of the loop and do it at the end with an exp2
        md2 *= mz2;
        // z  -> z^2 + c
        z = quatSq(z) + c;  

        trap = min( trap, vec4(abs(z.xyz),dot(z,z)) );

        mz2 = dot(z,z);
        if(mz2>4.0) break;
        n += 1.0;
    }
    
    oTrap = trap;

    return 0.25*sqrt(mz2/md2)*exp2(-n)*log(mz2);  // d = 0.5·|z|·log|z| / |dz|
}

float planeDE(vec3 p, vec4 n){
     return dot(p,n.xyz) + n.w;
}
float juliaDE(vec3 p, vec4 translation){
    vec4 zN = vec4(p, 0.0);
    vec4 zPrime = vec4(1, 0, 0, 0);
    
    for(int i =0; i < Iterations; i++){
        zN = quatSq(zN) + translation;
        zPrime = 2.0*hProduct(zN, zPrime);
    }
    // float planeDist = planeDE(p, normalize(vec4(0, 1, 0, 0)));
    // float bfact = smoothstep( length(p), 0, 1 );
    float l = length(zN);
    float jDist =  0.5*l*log(l)/length(zPrime);
    return jDist;
}

float DE(vec3 z)
{
    float Offset = 3.0;
    float r;
    int n = 0;
    float Scale = 2.0;
    while (n < Iterations) {
       if(z.x+z.y<0) z.xy = -z.yx; // fold 1
       if(z.x+z.z<0) z.xz = -z.zx; // fold 2
       if(z.y+z.z<0) z.zy = -z.yz; // fold 3	
       z = z*Scale - Offset*(Scale-1.0);
       n++;
    }
    return (length(z) ) * pow(Scale, -float(n));
}


float terrain(float x, float z){
    return sin(x)*sin(z);
}

float sdHexPrism( vec3 p, vec2 h )
{
  const vec3 k = vec3(-0.8660254, 0.5, 0.57735);
  p = abs(p);
  p.xy -= 2.0*min(dot(k.xy, p.xy), 0.0)*k.xy;
  vec2 d = vec2(
       length(p.xy-vec2(clamp(p.x,-k.z*h.x,k.z*h.x), h.x))*sign(p.y-h.x),
       p.z-h.y );
  return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}

float serpenskiSDF(vec3 z)
{
	vec3 a1 = vec3(1,1,1);
	vec3 a2 = vec3(-1,-1,1);
	vec3 a3 = vec3(1,-1,-1);
        vec3 a4 = vec3(-1,1,-1);
        vec3 c;
        int n = 0;
        float dist, d;
        float Scale = 2.0;
        while (n < Iterations){
            c = a1; dist = length(z-a1);
                d = length(z-a2); if (d < dist) { c = a2; dist=d; }
            d = length(z-a3); if (d < dist) { c = a3; dist=d; }
            d = length(z-a4); if (d < dist) { c = a4; dist=d; }
            z = Scale*z-c*(Scale-1.0);
            n++;
      //  Scale += 2;
	}

	return length(z) * pow(Scale, float(-n));
}




float fuckedSDF(vec3 p){
    vec3 d = abs(p) - vec3(1.0, 1.0, 1.0);

    float insideDistance = min(max(d.x, max(d.y, d.z)), 0.0);

    float outsideDistance = length(max(d, 0.0));

    return mod(insideDistance + outsideDistance, 1.0);
}

float cubeSDF(vec3 p){
    vec3 d = abs(p) - vec3(1.0, 1.0, 1.0);

    float insideDistance = min(max(d.x, max(d.y, d.z)), 0.0);

    float outsideDistance = length(max(d, 0.0));

    return (insideDistance + outsideDistance);
}

float sceneSDF(vec3 p){
    // float sphereDist = sdHexPrism(p, vec2(1.0, 1.0));
    float planeDist = planeDE(p, normalize(vec4(0, 1, 0, 0)));
    float bfact = smoothstep( length(p), 0, 1 );
    // // // return sphereDist;
    // return mix(sphereDist, planeDist, bfact);
     float juliaDistance = juliaDE(p, vec4(1, 1, 1,0));
    //  return juliaDistance;
    return mix(planeDist, juliaDistance, bfact);
}

// float sceneSDF_Quater(vec3 p, vec4 c){
//     // float sphereDist = sdHexPrism(p, vec2(1.0, 1.0));
//     // float planeDist = planeDE(p, normalize(vec4(0, 1, 0, 0)));
//     // float bfact = smoothstep( length(p), 0, 1 );
//     // // // return sphereDist;
//     // return mix(sphereDist, planeDist, bfact);
//      float juliaDistance = juli(p, c);
//      return juliaDistance;
//     // return mix(planeDist, juliaDistance, bfact);
// }
mat4 viewMatrix(vec3 eyeT, vec3 centre, vec3 up){
    vec3 f = normalize(centre - eyeT);
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);

   return mat4(
		vec4(s, 0.0),
		vec4(u, 0.0),
		vec4(-f, 0.0),
		vec4(0.0, 0.0, 0.0, 1)
	);
}

//efficent - re iniquo
vec3 estimateNormal( vec3 p ) 
{
    const float h = 0.0001; // or some other value
    const vec2 k = vec2(1,-1);
    return normalize( k.xyy*sceneSDF( p + k.xyy*h ) + 
                      k.yyx*sceneSDF( p + k.yyx*h ) + 
                      k.yxy*sceneSDF( p + k.yxy*h ) + 
                      k.xxx*sceneSDF( p + k.xxx*h ) );
}

vec3 calcNormal( in vec3 pos, in vec4 c )
{
    vec4 kk;
    vec2 e = vec2(1.0,-1.0)*0.5773*0.001;
    return normalize( e.xyy*juliaMap( pos + e.xyy, kk, c ) + 
					  e.yyx*juliaMap( pos + e.yyx, kk, c ) + 
					  e.yxy*juliaMap( pos + e.yxy, kk, c ) + 
					  e.xxx*juliaMap( pos + e.xxx, kk, c ) );
}

vec4 rayMarch(vec4 rayDirection, vec4 p, float start, float end){
    float depth = start;
    int steps;
    float totalDistance = 0.0;
   
    vec4 tmp;
    for(steps =0 ; steps < MAX_MARCHING_STEPS; steps++){
        float dist = juliaMap(p.xyz + depth * rayDirection.xyz, tmp, co);
        totalDistance += dist;

        if(dist < EPSILON){
            return vec4(depth, steps, totalDistance, 0);
        }
        depth += dist;
        if(depth >= end){
            return vec4(end, steps, totalDistance, 0);
        }
    }
    return vec4(end, steps, totalDistance, 0);
}


float softShadow(in vec3 ray_origin, in vec3 ray_direction, float mint, float tmax){
//   float tp = (255.0-ray_origin.y)/ray_direction.y; if( tp>0.0 ) tmax = min( tmax, tp );

    float res = 1.0;
    float t = mint;
    for( int i=0; i<20; i++ )
    {
		float h = sceneSDF( ray_origin + ray_direction*t );
        float s = clamp(8.0*h/t,0.0,1.0);
        res = min( res, s*s*(3.0-2.0*s) );
        t += clamp( h, 0.02, 0.10 );
        if( res<0.005 || t>tmax ) break;
    }
    return clamp( res, 0.0, 1.0 );
}
 vec4 shadows(vec3 p, vec3 light){
    vec3 lightDir = normalize(light - p);
    vec4 isShaded = rayMarch(vec4(lightDir, 1.0), vec4(normalize(p), 1.0), MIN_DIST, MAX_DIST);
    return isShaded;
 }


float juliaShadows(in vec3 ro, in vec3 rd, float mint, float k, in vec4 c){
    float res = 1.0;
    float t = mint;
    for( int i=0; i<64; i++ )
    {
        vec4 kk;
        float h = juliaMap(ro + rd*t, kk, c);
        res = min( res, k*h/t );
        if( res<0.001 ) break;
        t += clamp( h, 0.01, 0.5 );
    }
    return clamp(res,0.0,1.0);
}
 float shadow( in vec3 ro, in vec3 rd, float mint, float maxt )
{
    for( float t=mint; t<maxt; )
    {
        float h = sceneSDF(ro + rd*t);
        if( h<0.001 )
            return 0.0;
        t += h;
    }
    return 1.0;
}

vec3 lighting(vec3 p,  float ambientStrength, float specularStrength, float alpha){
    
    vec3 n = calcNormal(p, co);
    
    float diff = 0;
    vec3 ambient = ambientStrength*vec3(1,1,1);
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    float spec = 0;
    vec3 v = normalize(eye.xyz - p);

   
    for(int i =0 ; i < numLights; i++){
        vec3 lightDir = normalize(lights[i].pos - p);
        //vec3 reflection = normalize(2*(dot(n, -lightDir)*n - lightDir));
        vec3 reflection = reflect(n, -lightDir);
        diff += max(dot(n, lightDir), 0.0);
        diffuse += diff*lights[i].colour.rgb;
        diffuse *= juliaShadows(p, lightDir, 0.02, 255, co);
        spec += pow(max(dot(reflection, v), 0.0), alpha);
        specular += specularStrength*spec*lights[i].colour.rgb;
        }
    
    return diffuse + ambient + specular;
}

vec3 eyeLight(vec3 p,  float ambientStrength, float specularStrength, float alpha){
    vec3 n = estimateNormal(p);
    
    float diff = 0;
    vec3 ambient = ambientStrength*vec3(1,1,1);
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    float spec = 0;
    vec3 v = normalize(eye.xyz - p);

    vec4 shadowed = shadows(p, eye.xyz);
    if(length(eye.xyz - p) < shadowed.x){
        vec3 lightDir = normalize(eye.xyz - p);
        vec3 reflection = reflect(n, -lightDir);
        diff += max(dot(n, lightDir), 0.0);
        diffuse += diff*lightColour.rgb;
        spec += pow(max(dot(reflection, v), 0.0), alpha);
        specular += specularStrength*spec*lightColour.rgb;
    }
    
    return diffuse + ambient + specular;
}


vec3 rayDirection(float fieldOfView){
    vec2 xy = gl_FragCoord.xy - screenSize/2.0;
    float z = screenSize.y/tan(radians(fieldOfView)/2.0);
    return normalize(vec3(xy, -z));
}


vec4 scene(inout vec4 ray, float vignette){
    vec4 dist_steps = rayMarch(ray, eye, MIN_DIST, MAX_DIST);
    if(dist_steps.x > MAX_DIST - EPSILON){
        return background;
    }
    //-0.2 for better surface approximation
    vec3 p = eye.xyz + (dist_steps.x - 0.2)*ray.xyz;
    vec3 colour = lighting(p, 0.01, 1.0, 4);
    
    if (GLOW){
        colour *= dist_steps.y * vignette;
    }
    float a = 1.0/(1.0 + dist_steps.y *AMBIENT_OCCLUSION_STRENGTH);
    colour += (1.0 - a)*AMBIENT_OCCLUSION_COLOR_DELTA;
   
    // if(FOG){
    //     a = dist_steps.z / MAX_DIST;
	//     colour.xyz = (1.0 - a) * colour.xyz + a * background.xyz;
    //     colour += background*dist_steps.z;
    // }


    return vec4(colour, 1.0);
}

void main(){
    vec3 dir = rayDirection(45.0);

    mat4 viewToWorld = viewMatrix(eye.xyz, cameraCentre, cameraUp);
    vec4 worldDir = (viewToWorld * vec4(dir, 0.0));

    
    vec4 de_Colour = scene(worldDir, 0.1);
    fragColour = vec4(clamp(de_Colour.rgb, 0.0, 1.0), 1.0);
}