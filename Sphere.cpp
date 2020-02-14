#include "Sphere.h"



Sphere::Sphere(int longitudeCount, int latitudeCount, double radius) : Mesh(){
 

    double longitude = 2*M_PI/longitudeCount;
    double latitude = M_PI/latitudeCount;
    double longAngle, latAngle;
    double r = 1.0f/radius;
    double x, y, xy, z;
    double nx, ny, nz;

    //define a sphere as a function of two angles
    std::cout << longitudeCount << std::endl;
    std::cout << latitudeCount << std::endl;
    std::cout << "Longitude: " << longitude << std::endl;
    std::cout << "Latitude: " << latitude << std::endl;
    //polar iteration
    for(int i = 0; i < longitudeCount; i++){
        // std::cout << "i: " << i << std::endl;
        //equatorial iteration
        longAngle = M_PI/2 - i*longitude;
        xy = radius*cos(longAngle);
        z = radius*sin(longAngle);
        for(int j = 0; j < latitudeCount; j ++){
            // std::cout << "j: " << j << std::endl;
            latAngle = j*latitude;
            //sample our spherical parameterisation
            x = xy*cos(latAngle);
            y = xy*sin(latAngle);
            z = sin(latAngle);
            // std::cout << x << y << z << std::endl;
            Mesh::addVertex(x, y, z);
            nx = x*r;
            ny = y*r;
            nz = z*r;
            glm::vec3 normal(nx, ny,nz);
            Mesh::normals.push_back(normal);
        }
    }
    //for now
    // print();
    genIndices(longitudeCount, latitudeCount);
    attachMesh();
    // print();

}

Sphere::Sphere(bool cube, int subd){
    
}


std::vector<float> Sphere::buildUnitPositiveX(int subd){

    const float DEG2RAD = acos(-1)/180.0f;
    std::vector<float> verts;
    float n1[3];
    float n2[3];
    float v[3];
    float a1;
    float a2;

    int pointsPerRow = (int)pow(2, subd) + 1;

    for(unsigned int i = 0; i < pointsPerRow; ++i){
        a2 = DEG2RAD*(45.0f - 90.0f * i/(pointsPerRow - 1));
        n2[0] = -sin(a2);
        n2[1] = cos(a2);
        n2[2] = 0;

        for(unsigned int j = 0; j < pointsPerRow; ++j){
            
            a1 = DEG2RAD*(-45.0f + 90.0f * j/(pointsPerRow - 1));
            n1[0] = -sin(a1);
            n1[1] = 0;
            n1[2] = -cos(a1);

            v[0] = n1[1] * n2[2] - n1[2] * n2[1];
            v[1] = n1[2] * n2[0] - n1[0] * n2[2];
            v[2] = n1[0] * n2[1] - n1[1] * n2[0];

            // normalize direction vector
            float scale = 1 / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
            v[0] *= scale;
            v[1] *= scale;
            v[2] *= scale;

            // Triangle t(v);
            verts.push_back(v[0]);
            verts.push_back(v[1]);
            verts.push_back(v[2]);
        }
    }
    return verts;
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