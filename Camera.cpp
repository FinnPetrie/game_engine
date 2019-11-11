#include "Camera.h"

Camera::Camera(){
    cameraPos = new glm::vec3(0.0f, 0.0f, 3.0f);
    cameraTarget = new glm::vec3(0.0f, 0.0f, 0.0f);
    cameraDirection = new glm::vec3(glm::normalize(*cameraPos - *cameraTarget));

    up = new glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(*up, *cameraDirection));
    glm::vec3 cameraUp = glm::cross(*cameraDirection, cameraRight);

    view = new glm::mat4(glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                                     glm::vec3(0.0f, 0.0f, 0.0f),
                                    glm::vec3(0.0f, 1.0f, 0.0f)));
                                    
    cameraFront = new glm::vec3(0.0f, 0.0f, -1.0f);
    
    // cameraDirection->y = sin(glm::radians(pitch));
    // cameraDirection->x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    // cameraDirection->z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
}

void Camera::input(GLFWwindow *window){
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
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos){
    float xoffset = xpos - ypos;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
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