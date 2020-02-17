#include "Sphere.h"



Sphere::Sphere(int longitudeCount, int latitudeCount, float radius, bool DEBUG) : Mesh(false, DEBUG){
 
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

Sphere::Sphere(int subd, float radius, float step, glm::vec3 trans, bool DEBUG) : translation(new glm::vec3(trans)), Mesh(false, DEBUG){
    // translation = new glm::vec3(trans.x, trans.y, trans.z);
    cubeSphere(subd, radius, step);
}

Sphere::Sphere(int subd, float radius, float step, bool DEBUG) : Mesh(false, DEBUG){
    translation = new glm::vec3(0, 0, 0);
    cubeSphere(subd, radius, step);

}

void Sphere::cubeSphere(int subd, float radius, float step){
    
 
    cSphere = true;
    int x;
    
    float stepSize = step/float(subd);

    for(int face = 0; face < 6; face++){
        glm::vec3 *p;
        x =0;
        for(float s = 0; s <= 1.0f; s +=stepSize){
            x++;
            for(float t = 0; t <= 1.0f; t += stepSize){

                switch(face){
                    case 0:
                        p = new glm::vec3(1 - 2*s, 1-2*t, 1);
                        break;
                    case 1:
                        p = new glm::vec3(1,  1 - 2*s, 1 - 2*t);
                        break;
                    case 2:
                        p = new glm::vec3(1-2*s, -1, 1-2*t);
                        break;
                    case 3:
                        p = new glm::vec3(-1, 1-2*s, 1- 2*t);
                        break;
                    case 4: 
                        p = new glm::vec3(1-2*s, 1, 1-2*t);
                        break;
                    case 5:
                        p = new glm::vec3(1-2*s, 1-2*t, -1);
                        break;
                }

                // *p += translation;
                glm::vec3 n = glm::normalize(*p);
                addNormal(n);
                glm::vec3 v(n);
                v *= radius;
                v += *translation;
                addVertex(glm::vec3(v));
                }
            }
        }
    this->numIndices = x;

    genIndices(x, x);
    // attachMesh();
}

void Sphere::reInit(std::vector<glm::vec3> verts, std::vector<glm::vec3> norms){
    remapVertices(verts);
    remapNormals(norms);
    indices.clear();
    genIndices(numIndices, numIndices);
}

int Sphere::getSizeIndices(){
    return numIndices;
}

void Sphere::genIndices(int xNum, int yNum){
    int k1, k2;

    if(!cSphere){
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

        std::cout << "Not cube sphere " << std::endl;
            int k = yNum;
            std::cout << "xNum " << xNum << std::endl;
            for(int face = 0; face < 6; face++){
                for(int x = 0; x < xNum -1; x++){
                    k1 = (face*pow(xNum, 2)) + x*xNum +1;
                    k2 = k + k1;
                    std::cout << "K1 : " << k1 << std::endl;
                    for(int y = 0; y < yNum -1; y++, k1++, k2++){
                        
                        int a = k1;
                        int b = a -1;
                        int c = k2;
                        int d = c - 1;

                        addTriIndex(a, c, b);
                        addTriIndex(c, d, b);                        
                }
            }
        }
    }
}


void Sphere::multiplyVertex(double x, int index){
        vertices[index] *= x;
}


void Sphere::attachMesh() {
        Mesh::attachMesh();
       
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);

}

void Sphere::remapVertices(std::vector<glm::vec3> v){
    vertices.clear();
    for(int i =0 ; i < v.size(); i++){
        vertices.push_back(v[i]);
    }
}

void Sphere::remapNormals(std::vector<glm::vec3> n){
    normals.clear();
    for(int i =0 ; i < n.size(); i++){
        normals.push_back(n[i]);
    }
}

