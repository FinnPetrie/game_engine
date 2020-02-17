#ifndef MESH_H_
#define MESH_H_
#include "utils.h"
#include <vector>

class Mesh{

protected:
//change this to vec3s sooner or later
    std::vector<glm::vec3> vertices;
   
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    bool RAY_MARCHING = false;
    bool DEBUG = false;
    glm::vec3 colour;
    GLuint meshVAO;
    GLuint vertexBuffer;
    GLuint normalBuffer;
    GLuint normalVAO;
    GLuint indexBuffer;
    int numVertices;

    
    void calculateNormal();

public:
    
    Mesh(bool RAY_MARCHING, bool DEBUG);
    Mesh(bool DEBUG);
    virtual void draw();
    virtual void attachMesh();

    std::vector<glm::vec3> getVertices();
    
    //setters/getters
    glm::vec3 getVertex(int index);
    void setVertex(int index, glm::vec3);

    void bindMesh();
    void random();

    void addTriIndex(GLuint i, GLuint j, GLuint k);
    void addVertex(GLfloat x, GLfloat y, GLfloat z);
    void addVertex(glm::vec3 v);
    void addNormal(glm::vec3 n);
    
    void print(bool v, bool n);
    void test();
};

#endif