#ifndef SPHERE_H_
#define SPHERE_H_
#include "Triangle.h"
#include "Mesh.h"
#include "utils.h"

using VertexList = std::vector<glm::vec3>;
class Sphere : public Mesh{

    private:

    std::vector<glm::vec3> triangleList;
        double radius;
        void genIndices(int longitude, int latitude);
        std::vector<float> buildUnitPositiveX(int subd);
    public:
        Sphere(bool cube, int subd);
        Sphere(int subd);
        Sphere(int longitude, int latitude, double radius);
        void print();
        void attachMesh();

};

#endif