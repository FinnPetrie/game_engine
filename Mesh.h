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
    glm::vec3 *n;
    unsigned int index;
};

struct Half_Edge{
    Vertex *vert;
    Half_Edge *pair;
    Face *face;
    Half_Edge *next;

    void print(){
        std::cout << vert->v->x << "\n"<< vert->v->y << "\n" << vert->v->z << std::endl;
    }
};


struct Face{
    Half_Edge *edge;

    std::vector<Vertex *> verts;
    // std::vector<unsigned int> indices;
    glm::vec3 normal;

    // void calcNormal(){
    //     normal = glm::vec3(0,)
    //     Vertex *v = edge->vert;
    //     Vertex *vx = edge->next->vert;
    //     Vertex *vy = edge->next->next->vert;
    //     glm::vec3 e1 = *vx->v - *v->v;
    //     glm::vec3 e2 = *vx->v - *vy->v;

    //     this->normal = glm::cross(e1, e2);
    // }
};

class Mesh{


protected:

//change this to vec3s sooner or later
    std::vector<glm::vec3> vertices;
    std::vector<Face *> faceList;
    glm::vec3 colour;
    void calcHalfEdgeNormals();
    glm::vec3 faceNormal(Half_Edge *n);
    void reassignVertices();

    void createHalfEdges();
    
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    bool RAY_MARCHING = false;
    bool DEBUG = false;

    std::map<std::pair<unsigned int, unsigned int>, Half_Edge*> Edges; 

    
    GLuint meshVAO;
    GLuint vertexBuffer;
    GLuint normalBuffer;
    GLuint normalVAO;
    GLuint indexBuffer;
    int numVertices;

    void calcVertexNormals();
    virtual void createFaces();
    std::vector<Vertex *> vertexList;

public:
    
    Mesh(bool RAY_MARCHING, bool DEBUG);
    Mesh(bool DEBUG);
    virtual void draw();
    virtual void attachMesh();
    void sortVertices(std::vector<Vertex *> &verts);
    void printNormals();
    std::vector<glm::vec3> getVertices();
    void calculateNormals();
    void calculateFaceNormals();
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

    void printHalfEdges();
};

#endif