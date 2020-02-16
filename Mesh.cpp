#include "Mesh.h"


Mesh::Mesh(bool r, bool DEBUG) : RAY_MARCHING(false), DEBUG(DEBUG){
  
}

Mesh::Mesh(bool Ray_Marching) : RAY_MARCHING(Ray_Marching), DEBUG(false){
  
}




void Mesh::attachMesh(){
        glGenVertexArrays(1, &meshVAO);
        glBindVertexArray(meshVAO);

        glGenBuffers(1, &vertexBuffer);    
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
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
     
        // std::cout << "In draw" << std::endl;
        if(RAY_MARCHING){
            // std::cout << "In ray march " << std::endl;
       
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
       
        }else if (DEBUG){
            // std::cout << "DEBUGGING " << std::endl;
            glDrawArrays(GL_POINTS, 0, numVertices);
       
        }else{

            if(indices.size() > 0){
            // std::cout << "Drawing elements : " << std::endl;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
            
            }else{
                // std::cout << "Drawing tris" << std::endl;
                glDrawArrays(GL_TRIANGLES, 0, numVertices);
                
                }
        }
}


void Mesh::addTriIndex(GLuint i, GLuint j, GLuint k){
    indices.push_back(i);
    indices.push_back(j);
    indices.push_back(k);
    std::cout << indices.size() << std::endl;
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


void Mesh::print(bool v, bool n){
    for(int i =0 ;i < vertices.size(); i++){
        std::cout << i << "th vertex: " << glm::to_string(vertices[i]) << std::endl;
    }
   
}