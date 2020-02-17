#include "TerrainFace.hpp"


TerrainFace::TerrainFace(int subd, bool DEBUG): Mesh(DEBUG){
    //generate XZ plane
    float step = 1.0f/float(subd);
    int x =0;
    int y;
    for(float s = 0; s < 1.0f; s += step){
        x += 0;
        y = 0;
        for(float t = 0; t < 1.0f; t+=step){
            glm::vec3 v(1-2*s, 0, 1 - 2*t);
            glm::vec3 n(0, 1, 0);
            addVertex(v);
            addNormal(n);
            y += 1;
        }
    }

    genIndices(x, y);
    attachMesh();
}

void TerrainFace::genIndices(int xNum, int yNum){
    int k1, k2;
    int k = yNum;
               for(int x = 0; x < xNum -1; x++){
                    k1 =  x*xNum +1;
                    k2 = k + k1;
                    std::cout << "K1 : " << k1 << std::endl;
                    for(int y = 0; y < yNum -1; y++, k1++, k2++){
                        int a = k1;
                        int b = a -1;
                        int c = k2;
                        int d = c - 1;

                   
                        addTriIndex(a, c, b);
                        addTriIndex(c, d, b);                        

                    }
}
}