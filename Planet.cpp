#include "Planet.h"

Planet::Planet(int subd, double freq, size_t octaves, int seed){
    s = new Sphere(1, 1.0f, 0.5f, true);
    pearl = new SimplexNoise();
    float noise;
    
    std::vector<glm::vec3> oldVerts = s->getVertices();
    for(int i =0 ; i < s->getVertices().size() -3; i+=3){
        glm::vec3 v = s->getVertex(i);
       noise = 12*pearl->fractal(octaves,v.x, v.y, v.z);
    //    std::cout << noise << std::endl;
       v *= noise;
       s->setVertex(i, v);
    }    
    std::vector<glm::vec3> newVerts = s->getVertices();
    s->attachMesh();
    // for(int i =0 ; i < oldVerts.size() -3 ; i+=3){
    //     std::cout << "Old X : " << oldVerts[i] << " New X : " << newVerts[i] << "\nOld Y : " << oldVerts[i+1]
    //     << " New Y : " << newVerts[i+1] << "\nOld Z : " << oldVerts[i+2] << " New Z : " << newVerts[i+2] << std::endl;
    // }
}

void Planet::draw(){
    s->draw();
}