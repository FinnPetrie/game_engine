#ifndef CAMERA_H_
#define CAMERA_H_

#include "utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"

class Camera{
private:
    glm::vec3 *cameraFront;
    glm::vec3 *cameraPos;
    glm::vec3 *cameraTarget;
    glm::vec3 *cameraDirection;
    glm::vec3 *up;
   
    glm::mat4 *projection;
    glm::mat4 *model;
    glm::mat4 *view;

    
    
    float pitch, yaw;
    float speed;
    float lastX = 400, lastY = 300;


public:

    Camera(Window* window);
    Camera(glm::vec3 position, glm::vec3 front, float pitch, float yaw);

    //note, when raymarching a strange effect happens - directions of the camera seem to change while moving
    //maybe due to processing directions on the shader.
    void handleKeyboard(GLFWwindow* window);
    void handleMouse(GLFWwindow* window);
    
    
    glm::mat4 getView();
    glm::mat4 getModel();
    glm::mat4 getProjection();
    
    glm::vec4 getEye();
};

#endif