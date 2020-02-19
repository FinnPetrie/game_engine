#ifndef MESH_H_
#define MESH_H_
#include "utils.h"
#include <vector>
#include <algorithm>

struct Half_Edge;
struct Face;

struct Vertex{
    glm::vec3 *v;
    Half_Edge *edge;
};

struct Half_Edge{
    Vertex *vert;
    Half_Edge *pair;
    Face *face;
    Half_Edge *next;
};


struct Face{
    Half_Edge *edge;
};

class Mesh{


protected:

//change this to vec3s sooner or later
    std::vector<glm::vec3> vertices;
    glm::vec3 colour;

    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    bool RAY_MARCHING = false;
    bool DEBUG = false;

    
    GLuint meshVAO;
    GLuint vertexBuffer;
    GLuint normalBuffer;
    GLuint normalVAO;
    GLuint indexBuffer;
    int numVertices;


    virtual void createFaces();


public:
    
    Mesh(bool RAY_MARCHING, bool DEBUG);
    Mesh(bool DEBUG);
    virtual void draw();
    virtual void attachMesh();
    void sortVertices(std::vector<glm::vec3> &verts);

    std::vector<glm::vec3> getVertices();
    void calculateNormals();

    //setters/getters
    glm::vec3 getVertex(int index);
    void setVertex(int index, glm::vec3);

    void bindMesh();
    void random();

    void addTriIndex(GLuint i, GLuint j, GLuint k);
    void addVertex(GLfloat x, GLfloat y, GLfloat z);
    void addVertex(glm::vec3 v);
    void addNormal(glm::vec3 n);
    
    // bool vertexLesserComp(glm::vec3 &a, glm::vec3 &b);

    void print();
    void test();
};

#endif