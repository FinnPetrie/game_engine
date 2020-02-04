#include "Quad.h"

Quad::Quad(){
   GLfloat vertices[12] = {
      -1.0, -1.0, -1.0,
      -1.0, 1.0, -1.0,
      1.0, -1.0, -1.0,
      1.0, 1.0, -1.0
    };

    

    std::cerr << "Initialising QUAD" << std::endl;
    Mesh::numVertices = 12;

    glGenVertexArrays(1, &meshVAO);
    glBindVertexArray(meshVAO);
   // GLuint indices[6]={0,1,2,1,2,3};
    Mesh::indices = {0, 1, 2, 1, 2, 3};
    std::cout << indices.size() << std::endl;
    // for(int i : indices){
    //     std::cout << i << std::endl;
    // }
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
}

void Quad::draw(){
    // std::cout << "Drawing" << std::endl;
    Mesh::draw();
    

}