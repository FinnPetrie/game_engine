#ifndef LIGHT_H_
#define LIGHT_H_

#include "utils.h"


class Light{
    private:
        glm::vec3 *pos;
        glm::vec4 *colour;

    public:

    Light();
    Light(glm::vec3 pos, glm::vec4 colour);
    
    void updatePosition(float time);
    glm::vec3 getPosition();
    glm::vec4 getColour();

    void print();
};
#endif