#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 eye;

out vec3 vPos;
out vec3 vNormal;
out vec3 eyeDir;

void main(){
    //mat4 mv = modelview;
    vec4 worldPosition = model*vec4(aPos, 1.0);
    vPos = worldPosition.xyz;
    vNormal = mat3(transpose(inverse(model)))*normal;
    gl_Position = projection * view * worldPosition;
    eyeDir = normalize(eye.xyz -vPos);
}