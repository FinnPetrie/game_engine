#include "utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
private:
    glm::vec3 *cameraFront;
    glm::vec3 *cameraPos;
    glm::vec3 *cameraTarget;
    glm::vec3 *cameraDirection;
    glm::vec3 *up;
    glm::mat4 *view;

    
    float pitch, yaw;
    float speed;
    float lastX = 400, lastY = 300;


public:

    Camera();
    void input(GLFWwindow* window);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);

};

