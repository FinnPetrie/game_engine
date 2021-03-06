#include "Scene.h"
Scene::Scene(bool DEBUG){
    // Mesh *m;
    // m = new Mesh();
    // scene.push_back(*m);
    // Cube *c;
    // c = new Cube(DEBUG, true);
    // scene.push_back(*c);
    // Sphere *s = new Sphere(40, 40, 1);
    // Sphere *c = new Sphere(3, 1.0f, 0.1f, glm::vec3(10.0, 0, 0), DEBUG);
    // scene.push_back(*c);
    Planet *p = new Planet(20, 45.0, 5, 4000, DEBUG);
    planets.push_back(*p);
    // TerrainFace *t = new TerrainFace(5, DEBUG);
    // scene.push_back(*t);
    generateLights(2);
}

Scene::Scene(bool RAY_MARCH, bool DEBUG) : RAY_MARCH(RAY_MARCH), DEBUG(false){
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
        lights.push_back(*l);
    }
}

void Scene::sendLights(ShaderPipeline *shaders){
    shaders->sendLights("lights", lights);
    shaders->sendInt("numLights", lights.size());
}

void Scene::sendCentroids(ShaderPipeline *shader){
   
        shader->sendVec3("cent", planets[0].getCentroid());
        // std::cout << glm::to_string(p.getCentroid()) << std::endl;
    
}
void Scene::draw(){

    for(Mesh m : scene){
        m.draw();
    }

    for(Planet p : planets){
        p.draw();
    }
   
}