#include "Light.h"

Light::Light(){
    this->pos = new glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->colour = new glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}


Light::Light(glm::vec4 pos, glm::vec4 colour) : pos(new glm::vec4(pos)), colour( new glm::vec4 (colour)){

}

glm::vec4 Light::getPosition(){
    return *pos;
}

glm::vec4 Light::getColour(){
    return *colour;
}