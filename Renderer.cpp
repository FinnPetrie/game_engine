#include "Renderer.h"
#include <iostream>
Renderer::Renderer(){
    this->w = new Window(1080, 1040);
    err = glewInit();
    // this->s = new Shader("shader.vertex", GL_VERTEX_SHADER);
    createShaders();
}


void Renderer::createShaders(){
    std::vector<std::string> paths;
    std::vector<GLenum> types;

    paths.push_back("shader.vertex");
    paths.push_back("shader.frag");
    
    types.push_back(GL_VERTEX_SHADER);
    types.push_back(GL_FRAGMENT_SHADER);

    this->shaders = new ShaderPipeline(paths, types);

}
void Renderer::run(){
    // std::cout << err << std::endl;
    std::cout << GLEW_OK << std::endl;
    if(GLEW_OK != err){
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(err));
        return;
    }

    camera = new Camera();
    
    glUseProgram(shaders->getProgram());

    GLint loc = glGetUniformLocation(shaders->getProgram(), "modelview");
    std::cout << "Location: " << loc << std::endl;
    GLuint verArrId;
    glGenVertexArrays(1, &verArrId);
    glBindVertexArray(verArrId);

    static const GLfloat vertex_buffer[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    
    GLuint verBuff;
    glGenBuffers(1, &verBuff);
    glBindBuffer(GL_ARRAY_BUFFER, verBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);


    std::cout << "Running" << std::endl;
    while(!glfwWindowShouldClose(w->getWindow())){
        camera->input(w->getWindow());

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, verBuff);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        
        glfwSwapBuffers(w->getWindow());
    }
    
}

bool Renderer::deleteRenderer(){
    
}