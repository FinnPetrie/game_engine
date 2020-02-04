#include "Scene.h"

Scene::Scene(){
    // Mesh *m;
    // m = new Mesh();
    // scene.push_back(*m);
    Cube *c;
    c = new Cube();
    scene.push_back(*c);
    // Sphere *s = new Sphere(20, 20, 1.0);
    // scene.push_back(*s);

    Light *l;
    for(int i = 0; i < 2; i++){
       
        l = new Light();
        // l->print();
        lights.push_back(*l);

    }
    
}

Scene::Scene(bool RAY_MARCH) : RAY_MARCH(RAY_MARCH){
    Quad *q = new Quad;
    scene.push_back(*q);
}

std::vector<Light> Scene::getLights(){
    return lights;
}

void Scene::sendLights(ShaderPipeline *shaders){
    shaders->sendLights("lights", lights);
}

void Scene::draw(){

    for(Mesh m : scene){
        m.draw();
    }
   
}