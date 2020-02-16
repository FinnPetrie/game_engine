#include "Renderer.h"
#define WIDTH 3000
#define HEIGHT 2000
int main(int argc, char *argv[]){
    
    bool ray_march_enable = false;
    bool DEBUG = false;
    if(argc >= 2){
        if(strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "r") ==0){
            ray_march_enable = true;
        }
         if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "d") ==0){
            DEBUG = true;
        }
    }

    Renderer r(WIDTH, HEIGHT, ray_march_enable, DEBUG);
    r.run();
}

