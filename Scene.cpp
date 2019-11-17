#include "Scene.h"

Scene::Scene(){
    Mesh *m;
    for(int i = 0; i < 10; i++){
        m = new Mesh();
        scene.push_back(*m);
    }
    Light l;
    lights.push_back(l);
}

std::vector<Light> Scene::getLights(){
    return lights;
}

void Scene::draw(){

    for(Mesh m : scene){
        m.draw();
    }

}