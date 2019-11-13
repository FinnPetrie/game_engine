#ifndef WINDOW_H_
#define WINDOW_H_
#include "utils.h"
class Window{
    private:

    int width, height;
    GLFWwindow* window;

    public:

    Window();
    Window(int width, int height);
    GLFWwindow* getWindow();
    int getHeight();
    int getWidth();
    void destroy();

};

#endif