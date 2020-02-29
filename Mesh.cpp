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
      *f->v1->n += f->normal;
      *f->v2->n += f->normal;
      *f->v3->n += f->normal;
    //   std::cout << "Face norm: " << glm::to_string(f->normal) << std::endl;
    //   std::cout << glm::to_string(*f->v1->n) << std::endl;   
  }

  normals.clear();
  for(Face *f : faceList){
        normals.push_back(glm::normalize(*f->v1->n));
        normals.push_back(glm::normalize(*f->v2->n));
        normals.push_back(glm::normalize(*f->v3->n));

  }

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


void Mesh::calculateFaceNormals(){
    for(Face *f : faceList){
        // std::cout << f->v2->v << std::endl;;
        // std::cout << glm::to_string(*f->v1->v) << std::endl;
        glm::vec3 e1 = *f->v2->v - *f->v1->v;
        glm::vec3 e2 = *f->v2->v - *f->v3->v;
        // std::cout << glm::to_string(glm::normalize(glm::cross(e1, e2))) << std::endl;
        f->normal = glm::normalize(glm::cross(e1, e2));
    }
}

void Mesh::sortVertices(std::vector<glm::vec3> &verts){
    //may have to compare by absolute value
    std::sort(verts.begin(), verts.end(), [](glm::vec3 & a, glm::vec3 & b){
        if(a.x < b.x){
            return true;
        }else if(a.x == b.x){
            if(a.y < b.y){
                return true;
            }else if(a.y == b.y){
                if(a.z < b.z){
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

void Mesh::createFaces(){


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