#ifndef MESH_H_
#define MESH_H_
#include "utils.h"
#include <vector>

class Mesh{

private:
//change this to vec3s sooner or later
std::vector<GLfloat> vertices;
    GLuint verArrId;
    GLuint vertexBuffer;
public:

    Mesh();
    void draw();


};

#endif