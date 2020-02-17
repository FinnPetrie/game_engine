#ifndef TERRAIN_FACE_H_
#define TERAIN_FACE_H_
#include "Mesh.h"
#include "SimplexNoise.h"


class TerrainFace : public Mesh{
    private:

        void genIndices(int x, int y);
        void attachMesh();
        SimplexNoise *pearl;

    public:
        TerrainFace(int subd, bool DEBUG);
        
        void geoMorph();
};


#endif