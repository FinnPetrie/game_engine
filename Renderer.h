#ifndef RENDERER_H_
#define RENDERER_H_
#include "ShaderPipeline.h"
#include "Window.h"
#include "Scene.h"

#include "Camera.h"



class Renderer{
    private:
    Window *w;
    GLenum err;
    Camera *camera;;
    // Shader *s;
    ShaderPipeline *shaders;
    Scene *scene;

    void createShaders();

    public:
    Renderer();
    void run();
    bool deleteRenderer();

};

#endif