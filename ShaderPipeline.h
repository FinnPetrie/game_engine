#ifndef SHADERPIPELINE_H_
#define SHADERPIPELINE_H_
#include "Shader.h"

class ShaderPipeline{
    private:

    std::vector<Shader> shaders;
    GLint programID;
    bool link();

    public:
    ShaderPipeline(std::vector<std::string> paths, std::vector<GLenum> types);
    GLint getProgram();
    //implement later, for freeing shaders
    bool deleteShaders();
};

#endif