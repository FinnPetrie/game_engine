#ifndef ICOSPHERE_H_
#define ICOSPHERE_H_

#include "utils.h"
#include "Mesh.h"

#define X .525731112119133606 
#define Z .850650808352039932

class Icosphere : public Mesh{
    private:

    void subdivide();
    void Icosahedron(float r);
    void attachMesh();
    
    public:
    Icosphere(unsigned int subD);
};

#endif