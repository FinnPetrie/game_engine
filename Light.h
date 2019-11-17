#ifndef LIGHT_H_
#define LIGHT_H_

#include "utils.h"


class Light{
    private:
        glm::vec4 *pos;
        glm::vec4 *colour;

    public:

    Light();
    Light(glm::vec4 pos, glm::vec4 colour);

    glm::vec4 getPosition();
    glm::vec4 getColour();
};
#endif