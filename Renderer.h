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
    bool RAY_MARCH = false;
    void createShaders();

    public:
    Renderer();
    Renderer(int width, int height, bool rayMarch);
    void run();
    bool deleteRenderer();

};

#endif