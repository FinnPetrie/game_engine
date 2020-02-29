#include "Mesh.h"


Mesh::Mesh(bool r, bool DEBUG) : RAY_MARCHING(r), DEBUG(DEBUG){
  
}

void Mesh::attachMesh(){

        std::cout << "Attaching Mesh " << std::endl;
        glGenVertexArrays(1, &meshVAO);
        glBindVertexArray(meshVAO);

        glGenBuffers(1, &vertexBuffer);    
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0].x, GL_STATIC_DRAW);

      
        if(normals.size() > 0){
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals[0].x, GL_STATIC_DRAW);
        }
      
        if(indices.size() > 0){
            glGenBuffers(1, &indexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        }
}

void Mesh::calcVertexNormals(){
  for(Face *f : faceList){
      for(Vertex *v : f->verts){
        
          *v->n += f->normal;
      }
     
  }

  std::cout << " CALC " << std::endl;

//   normals.clear();
  for(Face *f : faceList){
      for(Vertex *v : f->verts){
        normals[v->index] = glm::vec3((glm::normalize(*v->n)));
     }
    }
    
}

// void Mesh::calcHalfEdgeNormals(){
//     normals.clear();
//     for(Vertex *v : vertexList){
//         Half_Edge *n_E = v->edge;
//         std::cout << "Fine " << std::endl;
       
//         std::cout << "After n Fine " << std::endl;

//         *v->n += n_E->face->normal;
//         std::cout << "Added to n " << std::endl;

//         n_E = n_E->pair->next;
//         while(n_E != v->edge){
//             std::cout << "navigating graph " << std::endl;
//             // n_E->face->calcNormal();
//             *v->n += n_E->face->normal;
//             std::cout << "Current value of vertex norm " << glm::to_string(*v->n) << std::endl;
//             n_E = n_E->pair->next;
//         }
//         std::cout << "Out " << std::endl;
//         *v->n = normalize(*v->n);
//         normals.push_back(*v->n);
//     }


// }

void Mesh::reassignVertices(){
        std::cout << vertices.size() << std::endl;

    vertices.clear();
    std::cout << vertexList.size() << std::endl;
    for(Vertex *v : vertexList){
        std::cout << glm::to_string(*v->v) << std::endl;
        vertices.push_back(*v->v);
    }
    indices.clear();
}

void Mesh::calculateNormals(){
    normals.clear();
    std::cout << "Sise of Norms : " <<normals.size() << std::endl;
    for(int i =0 ;i < indices.size(); i += 3){
        
        glm::vec3 a = vertices[indices[i]];
        glm::vec3 b = vertices[indices[i + 1]];
        glm::vec3 c = vertices[indices[i + 2]];

        glm::vec3 edge1 = b -a;
        glm::vec3 edge2 = b -c;
        
        glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
    }

    std::cout << "Sizse of norms : " << normals.size() << std::endl;
    std::cout << "index 2 : " << indices[1];


    std::cout << glm::to_string(vertices[indices[0]]) << std::endl;
    std::cout << glm::to_string(vertices[indices[1]]) << std::endl;
    std::cout << glm::to_string(vertices[indices[2]]) << std::endl;
}

void Mesh::createFaces(){
  // std::vector<Face> faces;
    Face *f;
    for(int i = 0; i < indices.size(); i+=3){
        f = new Face();
        glm::vec3 a = vertices[indices[i]];
        glm::vec3 b = vertices[indices[i + 1]];
        glm::vec3 c = vertices[indices[i + 2]];
        
        Vertex *v1 = new Vertex();
        Vertex *v2 = new Vertex();
        Vertex *v3 = new Vertex();

        v1->v = new glm::vec3(a);
        v1->index = indices[i];
        v1->n = new glm::vec3(0,0, 0);

        v2->v = new glm::vec3(b);
        v2->index = indices[i + 1];
        v2->n = new glm::vec3(0,0,0);

        v3->v = new glm::vec3(c);
        v3->index = indices[i +2];
        v3->n = new glm::vec3(0, 0, 0);

        std::vector<Vertex *> toSort = {v1, v2, v3};
        
        sortVertices(toSort);
       
        // f->indices = {indices[i], indices[i + 1], indices[i+2]};
        f->verts = std::vector<Vertex *>{toSort[0],toSort[1],toSort[2]};
        
        faceList.push_back(f);
    }


    // std::map<std::pair<unsigned int, unsigned int>, Half_Edge*> Edges; 
    // for(Face F : faces){
    //     std::cout << F.indices[0] << "\n" << F.indices[1] << "\n" << F.indices[2] << std::endl;
    // }

    createHalfEdges();
}

void Mesh::createHalfEdges(){
    std::ofstream pairs;
    pairs.open("Pairs.txt");
    // faceList = &faces;
    for(Face *F : faceList){

        std::pair<unsigned int, unsigned int> *edgePair;
        std::pair<unsigned int, unsigned int> *nextEdge;
        std::pair<unsigned int, unsigned int> *oppositeEdge;

        Vertex *vertex;
        //for each edge pair
        for(int i =0 ; i < 3; i++){
            edgePair = new std::pair<unsigned int, unsigned int>(F->verts[i]->index, F->verts[(i+1)%3]->index);
            // std::cout << "Edge pair: " << F->verts[i]->index << "\n" << F->verts[(i +1)%3]->index << std::endl;
            // std::cout << i << "\n" << (i + 1)%3 << std::endl;
            pairs << F->verts[i]->index << ": " << i << "\n" <<  F->verts[(i+1)%3]->index << ": " << (i+1) %3 <<std::endl;
          
            vertex = F->verts[i];
            
            Edges[*edgePair] = new Half_Edge();
            Edges[*edgePair]->face = F;
            Edges[*edgePair]->vert = vertex;
            vertex->edge = Edges[*edgePair];
            vertexList.push_back(vertex);
        } 
        
        for(int i =0 ; i < 3; i++){
            edgePair = new std::pair<unsigned int, unsigned int>(F->verts[i]->index, F->verts[(i+1)%3]->index);
            nextEdge = new std::pair<unsigned int, unsigned int>(F->verts[(i+1)%3]->index, F->verts[(i+2)%3]->index);
            oppositeEdge = new std::pair<unsigned int, unsigned int>(F->verts[(i+1)%3]->index, F->verts[i]->index);

            Edges[*edgePair]->next = Edges[*nextEdge];
            if(Edges.find(*oppositeEdge) != Edges.end()){
                    Edges[*edgePair]->pair = Edges[*oppositeEdge];
                    Edges[*oppositeEdge]->pair = Edges[*edgePair];
            }
        }
    }


    pairs.close();
    std::cout << "Closed pair " << std::endl;
    Mesh::calculateFaceNormals();
    std::cout << "Vertex : norms : "<< std::endl;
    Mesh::calcVertexNormals();
    // Mesh::reassigsnVertices();
    //currently the next thing 
    // Mesh::calcHalfEdgeNormals();
    }

    
void Mesh::calculateFaceNormals(){
    for(Face *f : faceList){
        // f->normal = new glm::vec3(0, 0, 0);
        std::cout << "Face norms " << std::endl;
        glm::vec3 e1 = *f->verts[1]->v - *f->verts[0]->v;
        glm::vec3 e2 = *f->verts[1]->v - *f->verts[2]->v;
        std::cout << glm::to_string(glm::normalize(glm::cross(e1, e2))) << std::endl;
        f->normal = glm::normalize(glm::cross(e1, e2));
    }
}

void Mesh::sortVertices(std::vector<Vertex *> &verts){
    //may have to compare by absolute value
    std::cout << "Printing sort " << std::endl;
    std::cout << verts[0]->v->x << std::endl;
    std::cout << glm::to_string(*verts[0]->v) <<std::endl;
    std::sort(verts.begin(), verts.end(), [](Vertex  *a, Vertex  *b){
         if(a->v->x < b->v->x){
            return true;
        }else if(a->v->x == b->v->x){
            if(a->v->y < b->v->y){
                return true;
            }else if(a->v->y == b->v->y){
                if(a->v->z < b->v->z){
                    return true;
                }
        }
    }
    return false;
    });   
}


//note to self, higher classes aren't getting their draw functions called
void Mesh::draw(){

        glBindVertexArray(meshVAO);
       

        if(RAY_MARCHING){
       
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
       
        }else if (DEBUG){
            glDrawArrays(GL_POINTS, 0, numVertices);
        }else{

            if(indices.size() > 0){
          
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
            
            }else{
                // std::cout << numVertices << std::endl;
                glDrawArrays(GL_TRIANGLES, 0, numVertices);
                
                }
        }
        
}


void Mesh::addTriIndex(GLuint i, GLuint j, GLuint k){
    indices.push_back(i);
    indices.push_back(j);
    indices.push_back(k);
    // std::cout << indices.size() << std::endl;
}

void Mesh::addVertex(glm::vec3 v){
    vertices.push_back(v);
}


void Mesh::addNormal(glm::vec3 n){
    normals.push_back(n);
}

void Mesh::addVertex(GLfloat x, GLfloat y, GLfloat z){
    glm::vec3 v(x, y, z);
    vertices.push_back(v);
}

glm::vec3 Mesh::getVertex(int index){
    glm::vec3 v(vertices[index]);
    return v;
}

std::vector<glm::vec3> Mesh::getVertices(){
    return this->vertices;
}

void Mesh::setVertex(int index, glm::vec3 v){
    vertices[index] = v;
  
}




void Mesh::print(){
    for(int i =0 ;i < vertices.size(); i++){
        std::cout << i << "th vertex: " << glm::to_string(vertices[i]) << std::endl;
        if(normals.size() > 0){
            std::cout << i << "the normal: " << glm::to_string(normals[i]) << std::endl;
            }
        }
}


void Mesh::printNormals(){
    for(int i = 0 ; i < normals.size(); i++){
        std::cout << glm::to_string(normals[i]) << std::endl;
    }
}
void Mesh::printHalfEdges(){
    unsigned int i = indices[0];
    unsigned int a = indices[1];
    
    std::pair<unsigned int, unsigned int> edg(i, a);
    Half_Edge *e = Edges[edg];
    
    e->print();
  
    
}