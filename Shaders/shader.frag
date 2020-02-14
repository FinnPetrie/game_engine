#version 330 core


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



vec3 lighting(vec3 n, float ambientStrength, float specularStrength, float alpha){
    
    float diff = 0;
    vec3 ambient = vec3(0,0,0);
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    float spec = 0;

    for(int i =0 ; i < 10; i++){
        vec3 lightDir = normalize(lights[i].pos - vPos);
        vec3 reflection = reflect(n, lightDir);

        ambient += ambientStrength*lights[i].colour.xyz;
        diff += max(dot(n, lightDir), 0.0);
        diffuse += diff*lights[i].colour.xyz;
        spec += pow(max(dot(reflection, normalize(eyeDir)), 0.0), alpha);
        specular += specularStrength*spec*lights[i].colour.xyz;
    }
    return diffuse + ambient + specular;
}


void main(){
    vec3 normal = normalize(vNormal);
    vec3 lightLevel = lighting(normal, 0.5, 1.5, 32);

    vec3 objectColour = vec3(0.5, 0.2, 0.78);

    vec3 result = lightLevel*objectColour;
    //fragColour = vec4(result, 1.0);
    fragColour = vec4(objectColour, 1.0);
}