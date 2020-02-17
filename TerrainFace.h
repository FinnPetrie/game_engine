#ifndef TERRAIN_FACE_H_
#define TERAIN_FACE_H_
#include "Mesh.h"


class TerrainFace : public Mesh{
    private:

        void genIndices(int x, int y);
        void attachMesh();
        
    public:
        TerrainFace(int subd, bool DEBUG);
        
};


#endif