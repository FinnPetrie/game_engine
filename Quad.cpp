#include "Quad.h"

Quad::Quad() : Mesh(true, false){


    vertices = {glm::vec3(-1.0, -1.0, -1.0),
                glm::vec3(-1.0, 1.0, -1.0),
                glm::vec3(1.0, -1.0, -1.0),
                glm::vec3(1.0, 1.0, -1.0)
                };
    
    std::cerr << "Initialising RAY-QUAD" << std::endl;
    

    Mesh::indices = {0, 1, 2, 1, 2, 3};

    attachMesh();
}


void Quad::attachMesh(){

    Mesh::attachMesh();
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

}
void Quad::draw(){
    std::cout << "Drawing" << std::endl;
    Mesh::draw();
    

}