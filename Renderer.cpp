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
    glEnable(GL_DEPTH_TEST);
    camera = new Camera(w);
    Mesh m;


    while(!glfwWindowShouldClose(w->getWindow())){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        camera->handleKeyboard(w->getWindow());
        camera->handleMouse(w->getWindow());

        glUseProgram(shaders->getProgram());
        
        shaders->modelViewProjection(camera);

        m.draw();

        glfwSwapBuffers(w->getWindow());
        glFlush();
    }
    
}

bool Renderer::deleteRenderer(){
    
}