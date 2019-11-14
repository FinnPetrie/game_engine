#ifndef RENDERER_H_
#define RENDERER_H_
#include "ShaderPipeline.h"
#include "Window.h"
#include "Mesh.h"
#include "Camera.h"



class Renderer{
    private:
    Window *w;
    GLenum err;
    Camera *camera;;
    // Shader *s;
    ShaderPipeline *shaders;

    void createShaders();

    public:
    Renderer();
    void run();
    bool deleteRenderer();

};

#endif