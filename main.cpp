#include "Renderer.h"
#define WIDTH 1920
#define HEIGHT 1080
int main(int argc, char *argv[]){
    
    bool ray_march_enable = false;
    
    if(argc >= 2){
        if(strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "r") ==0){
            ray_march_enable = true;
        }
    }

    Renderer r(WIDTH, HEIGHT, ray_march_enable);
    r.run();
}

