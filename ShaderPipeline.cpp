#include "ShaderPipeline.h"

ShaderPipeline::ShaderPipeline(std::vector<std::string> paths, std::vector<GLenum> types){
    assert(paths.size() == types.size());
    int counter = 0;
    Shader *shader;
    for (std::string path : paths){
        shader = new Shader(path, types[counter]);
        shaders.push_back(*shader);
        counter++;
    }

    link();
}


bool ShaderPipeline::link(){
    programID = glCreateProgram();
    for(Shader shader : shaders){
        glAttachShader(programID, shader.getShader());
    }
    glLinkProgram(programID);

    GLint linked;

    glGetProgramiv(programID, GL_LINK_STATUS, &linked);

    if(!linked){
        std::cout << "Linking failed" << std::endl;
        return false;
    }
    return true;
}

GLint ShaderPipeline::getProgram(){
    return programID;
}