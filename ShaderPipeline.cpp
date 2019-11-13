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
    this->programID = glCreateProgram();
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

    detach();
    deleteShaders();

    return true;
}

void ShaderPipeline::detach(){
    for(Shader shader : shaders){
        glDetachShader(programID, shader.getShader());
    }
}

void ShaderPipeline::deleteShaders(){
    for(Shader shader : shaders){
        glDeleteShader(shader.getShader());
    }
}
GLint ShaderPipeline::getProgram(){
    return programID;
}

void ShaderPipeline::sendMatrix(std::string name, glm::mat4 matrix){
    GLint location = glGetUniformLocation(programID, name.c_str());
    // std::cout << "Matrix " << name << " location : " << location << std::endl;
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}