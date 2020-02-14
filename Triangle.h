#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "utils.h"

class Triangle{

glm::vec3 *v1;
glm::vec3 *v2;
glm::vec3 *v3;

public:

Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
Triangle(float v[]);
glm::vec3 getIndices();

};

#endif