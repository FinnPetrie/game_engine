#include "Mesh.h"


Mesh::Mesh(){

    glGenVertexArrays(1, &verArrId);
    glBindVertexArray(verArrId);

    //    static const GLfloat vertex_buffer[] = {
    //     -1.0f, -1.0f, 0.0f,
    //     1.0f, -1.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f,
    // };
    GLfloat rand;
    for(int i =0; i < 9; i++){
        rand = std::rand()%100;
        std::cout << "Random vertex: " << rand << std::endl;
        vertices.push_back(rand);
    }

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    
}

void Mesh::draw(){
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
}