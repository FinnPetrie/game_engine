#include "Mesh.h"


Mesh::Mesh(){


    
    addVertex(-1.0f, -1.0f, 0.0f);
    addVertex(1.0f, -1.0f, 0.0f);
    addVertex(0.0f, 1.0f, 0.0f);
    calculateNormal();
    attachMesh();
}


void Mesh::random(){
    //    static const GLfloat vertex_buffer[] = {
    //     -1.0f, -1.0f, 0.0f,
    //     1.0f, -1.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f,
    // };
    

    std::cout << "Generating Mesh" << std::endl;
    GLfloat rand;
    for(int i =0; i < 9; i++){
        rand = std::rand()%100;
        // std::cout << "Random vertex: " << rand << std::endl;
        vertices.push_back(rand);
    }

    calculateNormal();
    // normals.push_back(normal);

    glGenBuffers(1, &vertexBuffer);    
    glGenBuffers(1, &normalBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer) * sizeof(GLfloat), vertex_buffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);


}



void Mesh::attachMesh(){
        glGenVertexArrays(1, &verArrId);
        glBindVertexArray(verArrId);

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
    // glm::vec3 normalG;
    // normal.x = (U.y*V.z) - (U.z*V.y);
    // normal.y = (U.z*V.x) - (U.x*V.z);
    // normal.z = (U.x*V.y) - (U.y*V.x);
    std::cout << "Normal: " << glm::to_string(normal) << std::endl;
  
    std::cout << "Normal test, point one: " << glm::dot(p2, normal) << std::endl;
    std::cout << "Normal test, point two: " << glm::dot(p1, normal) << std::endl;
    std::cout << "Normal test, point three: " << glm::dot(p3, normal) << std::endl;

    std::cout << "Norm test, U: " << glm::dot(normal, U) << std::endl;
    std::cout << "Norm test, V: " << glm::dot(normal, V) << std::endl;
}




void Mesh::draw(){
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        print(false, true);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDisableVertexAttribArray(1);
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
                case 0 :
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