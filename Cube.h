#include "Mesh.h"

class Cube: public Mesh{

    public:
        Cube();
        void draw();

    private:

        void attachMesh(float *v);
};
