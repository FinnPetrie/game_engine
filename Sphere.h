#ifndef SPHERE_H_
#define SPHERE_H_
#include "Triangle.h"
#include "Mesh.h"
#include "utils.h"

class Sphere : public Mesh{

    private:
    bool cSphere = false;
    
        std::vector<glm::vec3> triangleList;
        float radius;
        void genIndices(int longitude, int latitude);
        std::vector<float> buildUnitPositiveX(int subd);
        int numIndices;
        glm::vec3 *translation;


        void createFaces();

        void cubeSphere(int subd, float r, float step);
    public:

        Sphere(int subd, float r, float step, bool d);
        Sphere(int longitude, int latitude, float radius, bool d);
        Sphere(int subd, float r, float step, glm::vec3 trans, bool d);
        void reInit(std::vector<glm::vec3> verts, std::vector<glm::vec3> norms);
        void remapVertices(std::vector<glm::vec3> verts);
        void remapNormals(std::vector<glm::vec3> norms);

        void attachMesh();
        void multiplyVertex(double d, int index);
        int getSizeIndices();
};

#endif