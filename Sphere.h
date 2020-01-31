#ifndef SPHERE_H_
#define SPHERE_H_

#include "Mesh.h"
#include "utils.h"
class Sphere : public Mesh{

    private:
        std::vector<int> indices;
        double radius;
        void genIndices(int longitude, int latitude);
    public:

        Sphere(int longitude, int latitude);
    
        void draw();
        void print();
        void attachMesh();
};

#endif