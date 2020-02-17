#ifndef TERRAIN_FACE_H_
#define TERAIN_FACE_H_
#include "Mesh.h"


class TerrainFace : public Mesh{
    
    public:
        TerrainFace(int subd, bool DEBUG);
        void genIndices(int x, int y);
};


#endif