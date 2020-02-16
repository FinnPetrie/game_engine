#include "Icosphere.h"

Icosphere::Icosphere(unsigned int subd){
    Icosahedron(1.0f);

}


void Icosphere::Icosahedron(float r){
    static GLfloat vdata[12][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};
    float x, y, z;
    for(int i =0; i < 12; i++){
       for(int j =0; j < 3; j++){
           vertices.push_back(vdata[i][j]);
       }
    }


    // std::cout << vertices.size();
    // for(int i =0 ;i < vertices.size(); i++){
    //     std::cout << vertices[i] << std::endl;
    // }
static GLuint tindices[20][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}
    };

    // std::cout << tindices[0][1];
    for(int i =0 ;i < 20; i++){
       for(int j =0; j < 3; j++){
           int index = 3*tindices[i][j];
           indices.push_back(index);
           indices.push_back(index + 1);
           indices.push_back(index + 2);
       }
    }


        for (int i = 0; i < 20; i++) {    
    /* color information here */ 
    std::cout << "\nx "  << (vdata[tindices[i][0]][0]) << std::endl; 
    std::cout << "\nx "  << (vdata[tindices[i][0]][1]) << std::endl; 
    std::cout << "\nx "  << (vdata[tindices[i][0]][2]) << std::endl; 

    std::cout << " y " << (vdata[tindices[i][1]][0]) << std::endl; 
        std::cout << " y " << (vdata[tindices[i][1]][1]) << std::endl; 
    std::cout << " y " << (vdata[tindices[i][1]][2]) << std::endl; 

    std::cout << " z " << (vdata[tindices[i][2]][0]) << std::endl; 
        std::cout << " z " << (vdata[tindices[i][2]][1]) << std::endl; 
        std::cout << " z " << (vdata[tindices[i][2]][2]) << std::endl; 

    }

    std::cout << "\n\n\nCompared with other vertices: \n\n" << std::endl;
    for(int i = 0; i < vertices.size(); i++){
        std::cout << vertices[i] << std::endl;
    }

    // for(int i =0 ;i < indices.size(); i++){
    //     std::cout << indices[i] << std::endl;
    // }
    attachMesh();
}

void Icosphere::attachMesh(){
    numVertices = vertices.size();
    glGenVertexArrays(1, &meshVAO);
    glBindVertexArray(meshVAO);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices.size(), vertices.data(), GL_STATIC_DRAW);


    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
}

void Icosphere::subdivide(){
    
}