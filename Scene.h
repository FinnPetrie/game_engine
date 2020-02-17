#ifndef SCENE_H_
#define SCENE_H_
#include "Mesh.h"
#include "Light.h"
#include <vector>
#include "Sphere.h"
#include "Cube.h"
#include "Quad.h"
#include "ShaderPipeline.h"
#include "Planet.h"
#include "TerrainFace.h"



class Scene{

    private:
    std::vector<Mesh> scene;
    std::vector<Light> lights;
    std::vector<Planet> planets;
    void generateLights(int count);
    bool RAY_MARCH, DEBUG;
    public:

        Scene(bool DEBUG);
        Scene(bool RAY_MARCH, bool DEBUG);
        void draw();
        
        std::vector<Light> getLights();
        void sendLights(ShaderPipeline *shaders);
};
#endif