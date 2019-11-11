#include "Shader.h"


Shader::Shader(std::string path, GLenum shaderType){
    instantiate(path, shaderType);
}

std::string Shader::read(std::string path){
    std::string shaderCode;
    std::ifstream shader;
    shader.open(path);
    std::string line;
    while(!shader.eof()){
     std::getline(shader, line);
     shaderCode.append(line + "\n"); 
    }
    shader.close();
    return shaderCode;
    }


    //not compiling? What happening!
bool Shader::instantiate(std::string path, GLenum shaderType){
    shader = glCreateShader(shaderType);
    std::cout << "Shader value: " << shader << std::endl;
    std::string shaderCode = read(path);
    const char * code = shaderCode.c_str();
    glShaderSource(shader, 1, &code, NULL);
    std::cout << code << std::endl;
    glCompileShader(shader);
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    std::cout << compiled << std::endl;
    if(!compiled){
        generateLog();
        return false;
    }
}

void Shader::generateLog(){
    GLsizei infoLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
    char *infoLog;

    glGetShaderInfoLog(shader, infoLength, &infoLength, infoLog);
    if(infoLength){
      printf("Compilation failed: %s\n", infoLog);
    }

}

GLuint Shader::getShader(){
    return shader;
}