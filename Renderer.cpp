#include "Renderer.h"
#include <iostream>


Renderer::Renderer(){
    this->w = new Window(1080, 1040);
    err = glewInit();
    // this->s = new Shader("shader.vertex", GL_VERTEX_SHADER);
    createShaders();
}

Renderer::Renderer(int width, int height, bool rayMarch, bool DEBUG) :  RAY_MARCH(rayMarch), DEBUG(DEBUG){
    this->w = new Window(width, height);
    err = glewInit();
    createShaders();
}


void Renderer::createShaders(){
    std::vector<std::string> paths;
    std::vector<GLenum> types;
    
    if(!RAY_MARCH){
        paths.push_back("Shaders/shader.vert");
        // paths.push_back("Shaders/shader.geom");
        paths.push_back("Shaders/shader.frag");
        types.push_back(GL_VERTEX_SHADER);
        // types.push_back(GL_GEOMETRY_SHADER);
        types.push_back(GL_FRAGMENT_SHADER);
    }else{
        paths.push_back("Shaders/raymarch.vert");
        paths.push_back("Shaders/raymarch_julia.frag");
        types.push_back(GL_VERTEX_SHADER);
        types.push_back(GL_FRAGMENT_SHADER);
    }

    this->shaders = new ShaderPipeline(paths, types);
}

void Renderer::run(){

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_PROGRAM_POINT_SIZE);  

    if(GLEW_OK != err){
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(err));
        return;
    }

    glEnable(GL_DEPTH_TEST);

    //generate usual scene if not ray-marching, otherwise setup Quad with size WIDTH*HEIGHT so each pixel gets a fragment 

    if(!RAY_MARCH){
        scene = new Scene(DEBUG);
    }else{
        scene = new Scene(RAY_MARCH, DEBUG);
        std::cout << "Ray-Marching enabled" << std::endl;
    }
    
    camera = new Camera(w);

    while(!glfwWindowShouldClose(w->getWindow()) && (GLFW_KEY_ESCAPE != GLFW_PRESS)){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        camera->handleKeyboard(w->getWindow());
        camera->handleMouse(w->getWindow());
        //-------------------
        shaders->use();    
        shaders->sendVec2("screenSize", glm::vec2(w->getWidth(), w->getHeight()));
        //-------------------
        if(RAY_MARCH){
            // shaders->sendVec4("eye", glm::vec4(0, 0, 5.0, 0));
            shaders->sendMatrix("view", camera->getView());
            shaders->sendVec3("cameraUp", camera->getUp());
            shaders->sendVec3("cameraCentre", camera->getDirection());
        }
        //-------------------
        if(!RAY_MARCH){
      
        shaders->modelViewProjection(camera);
        
        }
        //-------------------
        
        shaders->sendVec4("eye", camera->getEye());
        scene->sendLights(shaders);
        scene->draw();

        //-------------------

        glfwSwapBuffers(w->getWindow());
        glFlush();
    }
    
}

bool Renderer::deleteRenderer(){
    
}