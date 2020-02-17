#include "Planet.h"

Planet::Planet(int subd, double freq, size_t octaves, int seed, bool DEBUG){
    s = new Sphere(4, 1.0f, 0.1f, DEBUG);
    pearl = new SimplexNoise();
    float noise;
    float scale = .007;
    std::vector<glm::vec3> oldVerts = s->getVertices();
    // s->print();
    std::vector<glm::vec3> newVerts;
    std::vector<glm::vec3> newNormals;
    for(int i =0 ; i < s->getVertices().size(); i++){
        glm::vec3 v = s->getVertex(i);
        std::cout << "V was: " << glm::to_string(v) << std::endl;
        noise = ((pearl->noise(v.x*scale, v.y*scale, v.z*scale) +1)*0.5);
        std::cout << "Noise applied " << noise << std::endl;
        v *= rand()%10;
    //    v *= noise;
        std::cout << "V is : " << glm::to_string(v) << std::endl;
    //    glm::vec3 normal = glm::normalize(v);
    //    s->setVertex(i, glm::vec3(0, 0, 0));
        newVerts.push_back(v);
        newNormals.push_back(glm::normalize(v));
    }
    // int num = s->getSizeIndices();
    s->reInit(newVerts, newNormals);
    // s->remapVertices(newVerts);
    // s->remapNormals(newNormals);
    // s->print();    
    
    s->attachMesh();
  
}


void Planet::draw(){
    s->draw();
}
