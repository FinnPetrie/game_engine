#ifndef SPHERE_H_
#define SPHERE_H_

#include "Mesh.h"
#include "utils.h"
class Sphere : public Mesh{

    private:


    public:

        Sphere(int longitude, int latitude);
    
        void draw();
        void print();

};

#endif