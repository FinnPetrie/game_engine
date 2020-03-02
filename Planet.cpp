#include "Planet.h"

Planet::Planet(int subd, double freq, size_t octaves, int seed, bool DEBUG){
    s = new Sphere(10, 1.0f, 0.1f, DEBUG);
//    s = new Sphere(50, 50,1.0f, DEBUG);
    //pearl = new SimplexNoise(10.0f, 3.0f, 1.25f, 0.5f);
    pearl = new SimplexNoise();
    float noise;
    float scale = 0.15f;
    // std::vector<glm::vec3> oldVerts = s->getVertices();
    // s->print();
    std::vector<glm::vec3> newVerts;
    std::vector<glm::vec3> newNormals;
    for(int i =0 ; i < s->getVertices().size(); i++){
        glm::vec3 v = s->getVertex(i);
        std::cout << "V was: " << glm::to_string(v) << std::endl;
        noise = (pearl->fractal(10, v.x*scale, v.y*scale, v.z*scale) + 1);
        std::cout << "Noise applied " << noise << std::endl;
        v *= noise;
       s->setVertex(i, v);
     
    }
    // int num = s->getSizeIndices();
    // s->reInit(newVerts, newNormals
    // s->remapVertices(newVerts);
    // s->remapNormals(newNormals);
    // s->print();    
    // s->calculateNormals();

    s->attachMesh();
    std::cout << "Printing half edges " << std::endl;
    //half edges result in segfault
    // s->printHalfEdges();
    // s->createFaces();
}

glm::vec3 Planet::getCentroid(){
    return s->getCentroid();
}


void Planet::draw(){
    s->draw();
}
