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


void Mesh::calculateNormal(){
    glm::vec3 p2(vertices[0]);
    glm::vec3 p1(vertices[1]);
    glm::vec3 p3(vertices[2]);
    glm::vec3 U = (p2 -p1);
    glm::vec3 V = (p3 - p1);

    glm::vec3 normal = glm::normalize(glm::cross(U, V));

    normals.push_back(normal);
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


void Mesh::print(){
    for(int i =0 ;i < vertices.size(); i++){
        std::cout << i << "th vertex: " << glm::to_string(vertices[i]) << std::endl;
        if(normals.size() > 0){
            std::cout << i << "th normal: " << glm::to_string(normals[i]) << std::endl;
            }
        }
}