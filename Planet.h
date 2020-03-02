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
    glm::vec3 getCentroid();
    Planet(int subd, double freq, size_t octaves, int seed, bool DEBUG);
    void draw();
  
};

#endif