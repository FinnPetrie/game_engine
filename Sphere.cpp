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
        createFaces();

        Mesh::attachMesh();

        numVertices = vertices.size();
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

void Sphere::createFaces(){
    // std::vector<Face> faces;
    Face *f;
    for(int i = 0; i < indices.size(); i+=3){
        f = new Face();
        glm::vec3 a = vertices[indices[i]];
        glm::vec3 b = vertices[indices[i + 1]];
        glm::vec3 c = vertices[indices[i + 2]];

        std::vector<glm::vec3> toSort = {a, b, c};
        for(int i =0 ;i < toSort.size(); i++){
            // std::cout << "From: " << glm::to_string(toSort[i]) << std::endl;
        }
        sortVertices(toSort);
        f->indices = {indices[i], indices[i + 1], indices[i+2]};
        f->verts = std::vector<glm::vec3>{a,b,c};
        for(int i =0 ; i < toSort.size(); i++){
            // std::cout << "To : " << glm::to_string(toSort[i]) << std::endl;
        }
        faceList.push_back(f);
    }


    // std::map<std::pair<unsigned int, unsigned int>, Half_Edge*> Edges; 
    // for(Face F : faces){
    //     std::cout << F.indices[0] << "\n" << F.indices[1] << "\n" << F.indices[2] << std::endl;
    // }
    std::ofstream pairs;
    pairs.open("Pairs.txt");
    // faceList = &faces;
    for(Face *F : faceList){
                std::cout << "\n " << F->indices[0] << "\t" << F->indices[1] << "\t" << F->indices[2] << std::endl;

        std::pair<unsigned int, unsigned int> *edgePair;
        std::pair<unsigned int, unsigned int> *nextEdge;
        std::pair<unsigned int, unsigned int> *oppositeEdge;

        Vertex *vertex;
        //for each edge pair
        for(int i =0 ; i < 3; i++){
            edgePair = new std::pair<unsigned int, unsigned int>(F->indices[i], F->indices[(i+1)%3]);
            // std::cout << "Edge pair: " << f->indices[i] << "\n" << f->indices[i+1] %3 << std::endl;
            // std::cout << i << "\n" << (i + 1)%3 << std::endl;
            pairs << F->indices[i] << "\n" << F->indices[(i+1)%3] <<std::endl;
            vertex = new Vertex();
            vertex->v = new glm::vec3(F->verts[i]);
            std::cout << glm::to_string(*vertex->v) << std::endl;
            vertex->n = new glm::vec3(0, 0, 0);
            switch(i){
                case 0:
                    F->v1 = vertex;
                    break;
                case 1:
                    F->v2 = vertex;
                    break;
                case 2:
                    F->v3 = vertex;
                    break;
            }
            
            Edges[*edgePair] = new Half_Edge();
            Edges[*edgePair]->face = F;
            Edges[*edgePair]->vert = vertex;
            vertex->edge = Edges[*edgePair];
            vertexList.push_back(vertex);
        } 
        
        for(int i =0 ; i < 3; i++){
            edgePair = new std::pair<unsigned int, unsigned int>(F->indices[i], F->indices[(i+1)%3]);
            nextEdge = new std::pair<unsigned int, unsigned int>(F->indices[(i+1)%3], F->indices[(i+2)%3]);
            oppositeEdge = new std::pair<unsigned int, unsigned int>(F->indices[(i+1)%3], F->indices[i]);

            Edges[*edgePair]->next = Edges[*nextEdge];
            if(Edges.find(*oppositeEdge) != Edges.end()){
                    Edges[*edgePair]->pair = Edges[*oppositeEdge];
                    Edges[*oppositeEdge]->pair = Edges[*edgePair];
            }
        }
    }
    pairs.close();
    Mesh::calculateFaceNormals();
    Mesh::calcVertexNormals();

    // std::cout << "Printing normals: " << std::endl;
    // Mesh::printNormals();
}
