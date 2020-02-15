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


Sphere::Sphere(int subd, float radius){
    //sample +Z face

    cubeSphere = true;
    for(float s = 0; s < 1.0f; s+= 0.1/float(subd)){
        for(float t = 0; t < 1.0f; t += 0.1/float(subd)){
            glm::vec3 p(1 - 2*s, 1-2*t, 1);
            glm::vec3 n = glm::normalize(p);
            normals.push_back(n);
            n *= radius;
            vertices.push_back(n.x);
            vertices.push_back(n.y);
            vertices.push_back(n.z);
        }
    }
    //sample -Z face
    for(float s = 0; s < 1.0f; s+= 0.1/float(subd)){
        for(float t = 0; t < 1.0f; t += 0.1/float(subd)){
            glm::vec3 p(1 - 2*s, 1-2*t, -1);
            glm::vec3 n = glm::normalize(p);
            normals.push_back(n);

            n *= radius;

            vertices.push_back(n.x);
            vertices.push_back(n.y);
            vertices.push_back(n.z);
        }
    }

    //sample +X face
       for(float s = 0; s < 1.0f; s+= 0.1/float(subd)){
        for(float t = 0; t < 1.0f; t += 0.1/float(subd)){
            glm::vec3 p(1, 1-2*t, 1 - 2*s);
            glm::vec3 n = glm::normalize(p);
            normals.push_back(n);

             n *= radius;

            vertices.push_back(n.x);
            vertices.push_back(n.y);
            vertices.push_back(n.z);
        }
    }

    //sample -X face
      for(float s = 0; s < 1.0f; s+= 0.1/float(subd)){
        for(float t = 0; t < 1.0f; t += 0.1/float(subd)){
            glm::vec3 p(-1, 1-2*t, 1 - 2*s);
            glm::vec3 n = glm::normalize(p);
            normals.push_back(n);

            n *= radius;

            vertices.push_back(n.x);
            vertices.push_back(n.y);
            vertices.push_back(n.z);
        }
    }

    //+Y
    for(float s = 0; s < 1.0f; s+= 0.1/float(subd)){
        for(float t = 0; t < 1.0f; t += 0.1/float(subd)){
            glm::vec3 p(1 - 2*s,   1, 1 - 2*t);
            glm::vec3 n = glm::normalize(p);
            normals.push_back(n);

            n *= radius;
            
            vertices.push_back(n.x);
            vertices.push_back(n.y);
            vertices.push_back(n.z);
        }
    }

        //-y
        int numIndices = 0;

      for(float s = 0; s < 1.0f; s+= 0.1/float(subd)){
        for(float t = 0; t < 1.0f; t += 0.1/float(subd)){
            glm::vec3 p(1 - 2*s,   -1, 1 - 2*t);
            glm::vec3 n = glm::normalize(p);
            normals.push_back(n);

            n *= radius;

            vertices.push_back(n.x);
            vertices.push_back(n.y);
            vertices.push_back(n.z);
        }
        numIndices++;
    }
    genIndices(6*numIndices, 6*numIndices);
    attachMesh();
}


void Sphere::genIndices(int xNum, int yNum){
    int k1, k2;

    if(!cubeSphere){
    for(int i =0; i < xNum; i++){
        k1 = i *(yNum + 1);
        k2 = k1 + yNum + 1;
        for(int j = 0; j < yNum; j++, k1++, k2++){
            if (i != 0){
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (xNum - 1)){
                indices.push_back(k1+1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
                }
            }
        }
    }else{

        //look more into how this works.
        const int k = xNum + 1;
        for(int face = 0; face < 6; face++){
            for(int i =0 ;i < xNum; i++){
               const bool bottom = i < (xNum/2);
                for(int j =0 ;j < yNum; j++){

                    const bool left = j < (xNum/2);
                    int a = (face*k +j) *k + i;
                    int b = (face*k +j) * k + i + 1;
                    int c = (face*k + j + 1) *k + i;
                    int d = (face *k + j + 1)* k + i + 1;
                    if(bottom ^ left){
                        indices.push_back(a);
                        indices.push_back(b);
                        indices.push_back(d);
                        indices.push_back(b);
                        indices.push_back(c);
                        indices.push_back(d);
                    }else{
                    indices.push_back(a);
                    indices.push_back(b);
                    indices.push_back(c);
                    indices.push_back(a);
                    indices.push_back(c);
                    indices.push_back(d);
                    }
                }
            }
            //else cubeSphere
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