#ifndef MESH_H_
#define MESH_H_
#include "utils.h"
#include <vector>

class Mesh{

protected:
//change this to vec3s sooner or later
    std::vector<GLfloat> vertices;
   
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    glm::vec3 colour;
    GLuint meshVAO;
    GLuint vertexBuffer;
    GLuint normalBuffer;
    GLuint normalVAO;
    GLuint indexBuffer;
    int numVertices;

    
    void calculateNormal();

public:
    
    Mesh();
    void draw();
    void attachMesh();
    void bindMesh();
    void random();
    void addVertex(GLfloat x, GLfloat y, GLfloat z);
    void print(bool v, bool n);
    void test();
};

#endif