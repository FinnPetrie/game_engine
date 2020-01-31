#include "Sphere.h"



Sphere::Sphere(int longitudeCount, int latitudeCount) : Mesh(){
 

    float longitude = 2*M_PI/longitudeCount;
    float latitude = M_PI/latitudeCount;
    float longAngle, latAngle;
    //define a sphere as a function of two angles

    std::cout << "Longitude: " << longitude << std::endl;
    std::cout << "Latitude: " << latitude << std::endl;
    //polar iteration
    for(float i = 0; i < longitude; i+= 0.1){
        std::cout << "i: " << i << std::endl;
        //equatorial iteration
        longAngle = M_PI/2 - i*longitude;
        for(float j = 0; j < latitude; j += 0.1){
            std::cout << "j: " << j << std::endl;
            latAngle = j*latitude;
            //sample our spherical parameterisation
            double x = cos(longAngle)*cos(latAngle);
            double y = cos(longAngle)*sin(latAngle);
            double z = sin(longAngle);
            // std::cout << x << y << z << std::endl;
            Mesh::addVertex(x, y, z);
            glm::vec3 normal(x, y,z);
            Mesh::normals.push_back(normal);
        }
    }
    //for now
    Mesh::numVertices = Mesh::vertices.size();

    attachMesh();
    print();

}

void Sphere::draw(){
    Mesh::draw();
}


void Sphere::genIndices(int longitudeCount, int latitudeCount){
    int k1, k2;
    for(int i =0; i < longitudeCount; i++){
        k1 = i *(latitudeCount + 1);
        k2 = k1 + latitudeCount + 1;
        for(int j = 0; j < latitudeCount; j++){
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
        glGenVertexArrays(1, &meshVAO);
        glBindVertexArray(meshVAO);

        glGenBuffers(1, &vertexBuffer);    
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

}

void Sphere::print(){
    Mesh::print(true, true);
}