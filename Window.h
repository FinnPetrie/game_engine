#ifndef WINDOW_H_
#define WINDOW_H_
#include "utils.h"
class Window{
    private:

    GLFWwindow* window;

    public:

    Window();
    Window(int width, int height);
    GLFWwindow* getWindow();
    void destroy();

};

#endif