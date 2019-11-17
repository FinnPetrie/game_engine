#version 330 core



in vec3 vPos;
in vec3 vNormal;
out vec3 colour;



struct Light {
    vec4 position;
    vec4 colour;
};

uniform LightUBlock{
    Light uLights[10];
};

uniform vec4 uEyePosition; 
uniform uint uLightCount;

vec3 lit(vec3 l, vec3 n, vec3 v){
    vec3 r_l = reflect(-l, n);
    float s = clamp(100.0*dot(r_l, v) - 97.0, 0.0, 1.0);
    vec3 highlightColour = vec3(2,2,2);
    vec3 uWarmColor = vec3(200, 24, 200);
    return mix(uWarmColor, highlightColour, s);
}
void main(){
    vec3 n = normalize(vNormal);
    vec3 v = normalize(uEyePosition.xyz - vPos);
    colour = vec3(0.0f, 1.0f, 0.0f);
    //outColour = vec4(uFUnlit, 1.0);

    /**for(uint i = 0u; i < uLightCount; i++){
        vec3 l = normalize(uLights[i].position.xyz - vPos);
        float NdL = clamp(dot(n, l), 0.0, 1.0);
        outColour.rgb += NdL*uLights[i].colour.rgb * lit(l, n, v);

    }*/
}