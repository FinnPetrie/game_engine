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
   std::vector<ShaderPipeline *> shades;
    Scene *scene;
    bool RAY_MARCH = false;
    bool NORMALS = false;
    bool DEBUG = false;
    void createShaders();

    public:
    Renderer();
    Renderer(int width, int height, bool rayMarch, bool DEBUG, bool NORMALS);
    void run();
    bool deleteRenderer();

};

#endif