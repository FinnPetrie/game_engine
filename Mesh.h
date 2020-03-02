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



struct Face{
    Half_Edge *edge;

    std::vector<Vertex *> verts;
    // std::vector<unsigned int> indices;
    glm::vec3 normal;

    void swapVerts(int i1, int i2){
        Vertex v1Copy = *verts[i1];
        
        verts[i1] = verts[i2];
        verts[i2] = &v1Copy;
    }
};

struct Half_Edge{
    Vertex *vert;
    Half_Edge *pair;
    Face *face;
    Half_Edge *next;

    void print(){
        std::cout << vert->v->x << "\n"<< vert->v->y << "\n" << vert->v->z << std::endl;
    }
    
    bool sameOrientation(Half_Edge *e){
        std::cout << "Checking orientatioN! " << std::endl;
        if(e->vert == vert){
            std::cout << "Same orientatio! " << std::endl;
            return true;
        }
        return false;
    }

    void rewind(){
        face->swapVerts(0, 2);
    }
    
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
    std::vector<Face *> queryFaces(Face *f);
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
    void orientate();
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