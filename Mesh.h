#ifndef MESH_H_
#define MESH_H_
#include "utils.h"
#include <vector>

class Mesh{

private:
//change this to vec3s sooner or later
    std::vector<GLfloat> vertices;
    std::vector<glm::vec3> normals;
    glm::vec3 normal;

    GLuint verArrId;
    GLuint vertexBuffer;
    GLuint normalBuffer;
    void calculateNormal();

public:

    Mesh();
    void draw();


};

#endif