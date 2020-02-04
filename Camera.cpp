#include "Camera.h"

Camera::Camera(Window* window){
    cameraPos = new glm::vec3(0.0f, 0.0f, 3.0f);
    cameraTarget = new glm::vec3(0.0f, 0.0f, -1.0f);
    cameraDirection = new glm::vec3(glm::normalize(*cameraPos - *cameraTarget));

    up = new glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(*up, *cameraDirection));
    glm::vec3 cameraUp = glm::cross(*cameraDirection, cameraRight);

    view = new glm::mat4(glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                                     glm::vec3(0.0f, 0.0f, 0.0f),
                                    glm::vec3(0.0f, 1.0f, 0.0f)));
                                    
    cameraFront = new glm::vec3(0.0f, 0.0f, 1.0f);
    speed = 0.01f;
    yaw = -90.0f;
    pitch = 0.0f;
    // pitch = 0;
    // cameraDirection->y = sin(glm::radians(pitch));
    // cameraDirection->x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    // cameraDirection->z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    model = new glm::mat4(1.0f);
    // glm::mat4 model = glm::mat4(1.0f);
    projection = new glm::mat4(glm::perspective(glm::radians(45.0f), (float)window->getHeight()/(float)window->getWidth(), 0.1f, 100.0f));  
  
}

void Camera::handleKeyboard(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        *cameraPos += speed**cameraFront;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        *cameraPos -= speed**cameraFront;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        *cameraPos -= glm::normalize(glm::cross(*cameraFront, *up)) * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        *cameraPos += glm::normalize(glm::cross(*cameraFront, *up)) * speed;
    }
    // std::cout << glm::to_string(*cameraPos) << std::endl;
}

void Camera::handleMouse(GLFWwindow* window){
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    
    if(pitch < -89.0f){
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = new glm::vec3(glm::normalize(front));
}

glm::mat4 Camera::getView(){
    return glm::lookAt(*cameraPos, *cameraPos + *cameraFront, *up);
}

glm::mat4 Camera::getModel(){
    return *model;
}

glm::mat4 Camera::getProjection(){
    return *projection;
}

glm::vec4 Camera::getEye(){
    
    return glm::vec4(*cameraPos, 1.0f);
}