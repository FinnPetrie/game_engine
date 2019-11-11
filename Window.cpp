#include "Window.h"

Window::Window(){


}

Window::Window(int width, int height){
    glfwInit();

    this->window = glfwCreateWindow(width, height, "standard", nullptr, nullptr);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    //this enables the context. We can use the 'get window context' to keep the engine encapsulated.
    //look into this.
    glfwMakeContextCurrent(window);

}

GLFWwindow* Window::getWindow(){
    return this->window;
}

void Window::destroy(){
    glfwDestroyWindow(this->window);
}