#include "Mesh.h"


Mesh::Mesh(){
  
}




void Mesh::attachMesh(){
        glGenVertexArrays(1, &meshVAO);
        glBindVertexArray(meshVAO);

        glGenBuffers(1, &vertexBuffer);    
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}


void Mesh::calculateNormal(){
    glm::vec3 p2(vertices[3], vertices[4], vertices[5]);
    glm::vec3 p1(vertices[0], vertices[1], vertices[2]);
    glm::vec3 p3(vertices[6], vertices[7], vertices[8]);
    glm::vec3 U = (p2 -p1);
    glm::vec3 V = (p3 - p1);

    glm::vec3 normal = glm::normalize(glm::cross(U, V));

    normals.push_back(normal);
}



//note to self, higher classes aren't getting their draw functions called
void Mesh::draw(){

        glBindVertexArray(meshVAO);
        // std::cout << "Size of indices : " << indices.size() << std::endl;
        // std::cout << "Size of vertices: " << vertices.size() << std::endl;
        if(indices.size() > 0){
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
            // glDrawArrays(GL_LINES, 0, numVertices);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
        }else{
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
        }

}


void Mesh::addIndex(GLuint i, GLuint j, GLuint k){
    indices.push_back(i);
    indices.push_back(j);
    indices.push_back(k);
}


void Mesh::addVertex(GLfloat x, GLfloat y, GLfloat z){
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}

void Mesh::print(bool v, bool n){

    if(v){
    int length = vertices.size()/3;
    for(int i =0 ; i < length; i++){
        for(int j = 0; j < 3; j++){
            std::string element = "";
            switch(j){
                case 0:
                    element = "X";
                    break;
                case 1:
                    element = "Y";
                    break;
                case 2:
                    element = "Z";
                    break;
                default:
                    break;
                }
            std::cout << element << ": " << vertices[i+j] << std::endl;
            }
        }
    }
    //removed normal printing
}