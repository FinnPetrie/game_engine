#include "Scene.h"

Scene::Scene(){
    // Mesh *m;
    // m = new Mesh();
    // scene.push_back(*m);
    // Cube *c;
    // c = new Cube();
    // scene.push_back(*c);
    // Sphere *s = new Sphere(20, 20, 1);
    Sphere *c = new Sphere(200, 200, 1);
    scene.push_back(*c);
    generateLights(2);
   
    
}

Scene::Scene(bool RAY_MARCH) : RAY_MARCH(RAY_MARCH){
    Quad *q = new Quad;
    scene.push_back(*q);
    Light l(glm::vec3(10.0, 10.0, -10.0), glm::vec4(0.5, 0.5, 0.3, 1.0));
    lights.push_back(l);
}

std::vector<Light> Scene::getLights(){
    return lights;
}


void Scene::generateLights(int count){
    Light *l;
    for(int i = 0; i < count; i++){
       
        l = new Light();
        // l->print();
        lights.push_back(*l);

    }
}
void Scene::sendLights(ShaderPipeline *shaders){
    shaders->sendLights("lights", lights);
    shaders->sendInt("numLights", lights.size());
}

void Scene::draw(){

    for(Mesh m : scene){
        m.draw();
    }
   
}