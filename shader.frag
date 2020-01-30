#version 330 core



in vec3 vPos;
in vec3 vNormal;
in vec3 fragPos;
out vec4 fragColour;

uniform vec3 lightPos;
uniform vec3 lightColour;
uniform vec3 objectColour;



void main(){
    vec3 lightP = vec3(0.0, 0.0, -10.0);
    vec3 lightCol = vec3(1.0, 1.0, 1.0);
    vec3 n = normalize(vNormal);
    vec3 v = normalize(lightPos - fragPos);
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColour;

    float diff = max(dot(n, v), 0.0);
    vec3 diffuse = diff*lightCol;
    vec3 objectColour = vec3(0.5, 0.2, 0.78);
    vec3 result = (ambient + diffuse) * objectColour;
    fragColour = vec4(result, 1.0);
}