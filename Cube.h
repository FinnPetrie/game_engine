#include "Mesh.h"

class Cube: public Mesh{

    public:
        Cube(bool d, bool p);

    private:
        bool procedural;
        unsigned int numIndices;
        void genIndices(int  x, int y);
        void proceduralCube(int subd, float steps);
        void attachMesh();

        void createFaces();
};
