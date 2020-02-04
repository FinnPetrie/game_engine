#version 330 core

const int MAX_MARCHING_STEPS = 255;
const float MIN_DIST = 0.0;
const float MAX_DIST = 100.0;
const float EPSILON = 0.0001;

in vec3 vPos;
in vec3 vNormal;
in vec3 eyeDir;
in vec3 eyeRes;

out vec4 fragColour;


uniform vec2 screenSize;

struct Light{
    vec3 pos;
    vec4 colour;
};

uniform Light lights[10];
uniform int numLights;
uniform vec3 objectColour;

float sphereSDF(vec3 p){
    return length(p) - 1.0;
}


vec3 estimateNormal(vec3 p){
    return(normalize(vec3(sphereSDF(vec3(p.x + EPSILON, p.y, p.z )) - sphereSDF(vec3(p.x -EPSILON, p.y, p.z )),
                          sphereSDF(vec3(p.x, p.y + EPSILON, p.z)) - sphereSDF(vec3(p.x, p.y - EPSILON, p.z)),
                          sphereSDF(vec3(p.x, p.y, p.z + EPSILON)) - sphereSDF(vec3(p.x, p.y, p.z - EPSILON)))));
    
}   

vec3 lighting(vec3 p, float ambientStrength, float specularStrength, float alpha){
    vec3 n = estimateNormal(p);

    float diff = 0;
    vec3 ambient = ambientStrength*vec3(1,1,1);
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    float spec = 0;

    for(int i =0 ; i < numLights; i++){
        vec3 lightDir = normalize(lights[i].pos - p);
        vec3 reflection = normalize(2*(dot(n, -lightDir)*n - lightDir));

        ambient += ambientStrength*lights[i].colour.xyz;
        diff += max(dot(n, lightDir), 0.0);
        diffuse += diff*lights[i].colour.xyz;
        spec += pow(max(dot(reflection, normalize(eyeDir)), 0.0), alpha);
        specular += specularStrength*spec*lights[i].colour.xyz;
    }
    return diffuse + ambient + specular;
}

float rayMarch(vec3 marchingDirection, float start, float end){
    float depth = start;
    for(int i =0 ; i < MAX_MARCHING_STEPS; i++){
        float dist = sphereSDF(eyeRes + depth * marchingDirection);
        if(dist < EPSILON){
            return depth;
        }
        depth += dist;

        if(depth >= end){
            return end;
        }
    }
    return end;
}

vec3 rayDirection(float fieldOfView){
    vec2 xy = gl_FragCoord.xy - screenSize/2.0;
    float z = screenSize.y/tan(radians(fieldOfView)/2.0);
    return normalize(vec3(xy, -z));
}


void main(){
    vec3 dir = rayDirection(45.0);
    float dist = rayMarch(dir, MIN_DIST, MAX_DIST);
    
    if(dist > MAX_DIST -EPSILON) {
        fragColour= vec4(0.0, 0.0, 0.0, 0.0);
        return;
    }

    vec3 p = eyeRes + dist * dir;
    vec3 colour = lighting(p, 0.5, 1.0, 4);
    fragColour = vec4(colour, 1.0);
}