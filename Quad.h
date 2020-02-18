#include "Mesh.h"

class Quad: public Mesh{


    public: 
    
        Quad();
        void draw();
        void attachMesh();

        void createFaces();
};