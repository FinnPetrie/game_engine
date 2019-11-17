#ifndef SCENE_H_
#define SCENE_H_
#include "Mesh.h"
#include "Light.h"
#include <vector>


class Scene{

private:
std::vector<Mesh> scene;
std::vector<Light> lights;
public:

Scene();

void draw();
std::vector<Light> getLights();

};
#endif