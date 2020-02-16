#ifndef PLANET_H_
#define PLANET_H_
#include "utils.h"
#include "Sphere.h"
#include "SimplexNoise.h"

class Planet{

    private:
        Sphere* s;
        SimplexNoise *pearl;
    public:

    Planet(int subd, double freq, size_t octaves, int seed);
    void draw();
    

};

#endif