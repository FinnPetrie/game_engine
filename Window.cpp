#include "Window.h"

Window::Window(){


}

Window::Window(int width, int height) : width(width), height(height){
    glfwInit();
    
    this->window = glfwCreateWindow(width, height, "standard", nullptr, nullptr);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    //this enables the context. We can use the 'get window context' to keep the engine encapsulated.
    //look into this.
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWwindow* Window::getWindow(){
    return this->window;
}

void Window::destroy(){
    glfwDestroyWindow(this->window);
}

int Window::getHeight(){
    return height;
}

int Window::getWidth(){
    return width;
}