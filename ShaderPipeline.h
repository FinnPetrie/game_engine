#ifndef SHADERPIPELINE_H_
#define SHADERPIPELINE_H_
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

class ShaderPipeline{
    private:

    std::vector<Shader> shaders;
    GLint programID;
    bool link();
    void detach();
    void deleteShaders();
    public:
    ShaderPipeline(std::vector<std::string> paths, std::vector<GLenum> types);
    GLint getProgram();
    //implement later, for freeing shaders

    bool deleteProgram();
    void sendMatrix(std::string name, glm::mat4 matrix);
};

#endif