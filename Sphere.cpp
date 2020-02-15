#include "Sphere.h"



Sphere::Sphere(int longitudeCount, int latitudeCount, float radius) : Mesh(){
 
    float latitudeStep = 2*M_PI/latitudeCount;
    float longitudeStep = M_PI/longitudeCount;

    float longAngle, latAngle;
    float r = 1.0f/radius;
    float x, y, xy, z;
    float nx, ny, nz;

    //define a sphere as a function of two angles
    for(int i =0 ; i <= longitudeCount; ++i){
        longAngle = M_PI/2 - i*longitudeStep;
        
        xy = radius*cosf(longAngle);
        z = radius*sinf(longAngle);
        
        for(int j = 0; j <= latitudeCount; ++j){

            latAngle = j * latitudeStep;

            x = xy*cosf(latAngle);
            y = xy*sinf(latAngle);
            addVertex(x, y, z);

            nx = r * x;
            ny = r * y;
            nz = r * z;

            glm::vec3 normal(nx, ny, nz);
            normals.push_back(normal);
        }
    
    }

    genIndices(longitudeCount, latitudeCount);
    attachMesh();
}



void Sphere::genIndices(int longitudeCount, int latitudeCount){
    int k1, k2;
    for(int i =0; i < longitudeCount; i++){
        k1 = i *(latitudeCount + 1);
        k2 = k1 + latitudeCount + 1;
        for(int j = 0; j < latitudeCount; j++, k1++, k2++){
            if (i != 0){
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (longitudeCount - 1)){
                indices.push_back(k1+1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}


void Sphere::attachMesh(){
        numVertices = vertices.size();
        std::cout << "Attaching mesh " << std::endl;
        std::cout << normals.size();
        glGenVertexArrays(1, &meshVAO);
        glBindVertexArray(meshVAO);
        std::cerr << meshVAO << std::endl;
        glGenBuffers(1, &vertexBuffer);    
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, Mesh::normals.size() * sizeof(glm::vec3), &normals[0].x, GL_STATIC_DRAW);

        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);

}

void Sphere::print(){
    Mesh::print(true, true);
}