#version 330 core

const int MAX_MARCHING_STEPS = 255;
const float MIN_DIST = 0.0;
const float MAX_DIST = 100.0;
const float EPSILON = 0.0001;

in vec3 vPos;
in vec3 vNormal;
in vec3 eyeDir;
in vec3 eyeThree;

out vec4 fragColour;

uniform vec2 screenSize;

struct Light{
    vec3 pos;
    vec4 colour;
};

uniform Light lights[10];
uniform vec3 objectColour;

float sphereSDF(vec3 p){
    return length(p) - 1.0;
}


float rayMarch(vec3 marchingDirection, float start, float end){
    float depth = start;
    for(int i =0 ; i < MAX_MARCHING_STEPS; i++){
        float dist = sphereSDF(eyeThree + depth * marchingDirection);
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

vec3 rayDirection(float fieldOfView, vec2 fragPos){
    vec2 xy = fragPos - screenSize/2.0;
    float z = screenSize.y/tan(radians(fieldOfView)/2.0);
    return normalize(vec3(xy, -z));
}


void main(){


    vec3 dir = rayDirection(45.0, gl_FragCoord.xy);
    float dist = rayMarch(dir, MIN_DIST, MAX_DIST);
    if(dist > MAX_DIST -EPSILON) {
        fragColour= vec4(0.0, 0.0, 0.0, 0.0);
        return;
    }
    fragColour = vec4(gl_FragCoord.xy, 0.0, 1.0);
    
}