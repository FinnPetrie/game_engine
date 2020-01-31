#include "Scene.h"

Scene::Scene(){
    Mesh *m;
    m = new Mesh();
    scene.push_back(*m);
    Light *l;
    for(int i = 0; i < 10; i++){
       
        l = new Light();
        // l->print();
        lights.push_back(*l);

    }
    
}

std::vector<Light> Scene::getLights(){
    return lights;
}

void Scene::sendLights(ShaderPipeline *shaders){
    shaders->sendLights("lights", lights);
}

void Scene::draw(){

    for(Mesh m : scene){
        m.draw(36);
    }

   
}