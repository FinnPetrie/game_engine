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

    calculateNormal();
    normals.push_back(normal);

    glGenBuffers(1, &vertexBuffer);    
    glGenBuffers(1, &normalBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

}


void Mesh::calculateNormal(){
    glm::vec3 p2(vertices[3], vertices[4], vertices[5]);
    glm::vec3 p1(vertices[0], vertices[1], vertices[2]);
    glm::vec3 p3(vertices[6], vertices[7], vertices[8]);
    glm::vec3 U = (p2 -p1);
    glm::vec3 V = (p3 - p1);

    // glm::vec3 normalG;
    normal.x = (U.y*V.z) - (U.z*V.y);
    normal.y = (U.z*V.x) - (U.x*V.z);
    normal.z = (U.x*V.y) - (U.y*V.x);

}


void Mesh::draw(){
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDisableVertexAttribArray(1);
}