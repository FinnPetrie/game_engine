#ifndef SCENE_H_
#define SCENE_H_
#include "Mesh.h"
#include <vector>


class Scene{

private:
std::vector<Mesh> scene;

public:

Scene();

void draw();

};
#endif