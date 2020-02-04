#include "Renderer.h"
#include <iostream>


Renderer::Renderer(){
    this->w = new Window(1080, 1040);
    err = glewInit();
    // this->s = new Shader("shader.vertex", GL_VERTEX_SHADER);
    createShaders();
}

Renderer::Renderer(int width, int height, bool rayMarch) :  RAY_MARCH(rayMarch){
    this->w = new Window(width, height);
    err = glewInit();
    createShaders();
}


void Renderer::createShaders(){
    std::vector<std::string> paths;
    std::vector<GLenum> types;
    if(!RAY_MARCH){
    paths.push_back("Shaders/shader.vertex");
    paths.push_back("Shaders/shader.frag");
    }else{
        paths.push_back("Shaders/raymarch.vertex");
        paths.push_back("Shaders/raymarch.frag");
    }
    types.push_back(GL_VERTEX_SHADER);
    types.push_back(GL_FRAGMENT_SHADER);

    this->shaders = new ShaderPipeline(paths, types);

}
void Renderer::run(){
    // std::cout << err << std::endl;
    std::cout << GLEW_OK << std::endl;
    glEnable(GL_COLOR_MATERIAL);

    if(GLEW_OK != err){
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(err));
        return;
    }
    glEnable(GL_DEPTH_TEST);
    camera = new Camera(w);

    if(!RAY_MARCH){
    scene = new Scene();
    }else{
        std::cout << "Ray-Marching enabled" << std::endl;
    }

    while(!glfwWindowShouldClose(w->getWindow())){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        
        
        //-------------------
        shaders->use();    
        shaders->sendVec2("screenSize", glm::vec2(w->getHeight(), w->getWidth()));

        if(RAY_MARCH){
            shaders->sendVec4("eye", glm::vec4(0, 0, 5.0, 0));
        }
        
        //-------------------
        if(!RAY_MARCH){
        camera->handleKeyboard(w->getWindow());
        camera->handleMouse(w->getWindow());

        shaders->sendVec4("eye", camera->getEye());

        shaders->modelViewProjection(camera);
        scene->sendLights(shaders);
        scene->draw();
        }

        glfwSwapBuffers(w->getWindow());
        glFlush();
    }
    
}

bool Renderer::deleteRenderer(){
    
}