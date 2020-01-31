#include "Light.h"

Light::Light(){

        float x = rand()%10 +1;
        float y = rand()%10 + 1;
        float z = rand()%10 + 1;

        float r = float(rand())/(RAND_MAX);
        float g = float(rand())/(RAND_MAX);
        float b = float(rand())/(RAND_MAX);

        this->pos = new glm::vec3(x, y, z);
        this->colour = new glm::vec4(r, g, b, 1.0f);
}


Light::Light(glm::vec3 pos, glm::vec4 colour) : pos(new glm::vec3(pos)), colour( new glm::vec4 (colour)){

}

glm::vec3 Light::getPosition(){
    return *pos;
}

glm::vec4 Light::getColour(){
    return *colour;
}

void Light::print(){
    std::cout << glm::to_string(*pos) << std::endl;
    std::cout << glm::to_string(*colour) << std::endl;
}