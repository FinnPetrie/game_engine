#ifndef SCENE_H_
#define SCENE_H_
#include "Mesh.h"
#include "Light.h"
#include <vector>
#include "Sphere.h"
#include "Cube.h"
#include "Quad.h"
#include "Icosphere.h"
#include "ShaderPipeline.h"


class Scene{

    private:
    std::vector<Mesh> scene;
    std::vector<Cube> cubes;
    std::vector<Light> lights;
    void generateLights(int count);
    bool RAY_MARCH;
    public:

        Scene();
        Scene(bool RAY_MARCH);
        void draw();
        
        std::vector<Light> getLights();
        void sendLights(ShaderPipeline *shaders);
};
#endif