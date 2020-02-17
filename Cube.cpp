#include "Cube.h"

Cube::Cube(bool DEBUG, bool procedural) : Mesh(false, DEBUG), procedural(procedural){




//      vertices = {
//     glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f),
//      glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f), 
//      glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), 
//      glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f), 
//     glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), 
//    glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), 

//    glm::vec3( -0.5f, -0.5f,  0.5f),  glM::vec0.0f,  0.0f, 1.0f,
//      0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

//     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
 
//      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

//     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

//     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//     };

    // glGenVertexArrays(1, &meshVAO);
    // glGenBuffers(1, &vertexBuffer);

    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindVertexArray(meshVAO);

    // // position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // // normal attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // Mesh::numVertices = 36;

    if(procedural){
        proceduralCube(5, 0.1f);
    }
    attachMesh();
}

void Cube::proceduralCube(int subd, float step){
    float stepSize = step/float(subd);
    std::cout << "Step size: " << stepSize << std::endl;
    int x, y;


    for(int face = 0; face < 6; face++){
        glm::vec3 *p;
        x =0;
        glm::vec3 *n;
        for(float s = 0; s <= 1.0f; s +=stepSize){
            x++;
            y = 0;
            for(float t = 0; t <= 1.0f; t += stepSize){

                switch(face){
                    case 0:
                        p = new glm::vec3(1 - 2*s, 1-2*t, 1);
                        n = new glm::vec3(0, 0, 1);
                        break;
                    case 1:
                        p = new glm::vec3(1,  1 - 2*s, 1 - 2*t);
                        n = new glm::vec3(1, 0, 0);
                        break;
                    case 2:
                        p = new glm::vec3(1-2*s, -1, 1-2*t);
                        n = new glm::vec3(0, -1, 0);
                        break;
                    case 3:
                        p = new glm::vec3(-1, 1-2*s, 1- 2*t);
                        n = new glm::vec3(-1, 0, 0);
                        break;
                    case 4: 
                        p = new glm::vec3(1-2*s, 1, 1-2*t);
                        n = new glm::vec3(0, 1, 0);
                        break;
                    case 5:
                        p = new glm::vec3(1-2*s, 1-2*t, -1);
                        n = new glm::vec3(0, 0, -1);
                        break;
                }
                y += 1;

                // *p += translation;
                addNormal(*n);
                addVertex(*p);
                }
            }
        }
    print();
    std::cout << "X: " << x << "\nY: " << y << std::endl;
    this->numIndices = x;

    genIndices(x, y);
    // attachMesh();
}


void Cube::genIndices(int xNum, int yNum){
    int k1, k2;
      int k = yNum;
            // std::cout << "xNum " << xNum << std::endl;
            for(int face = 0; face < 6; face++){
                for(int x = 0; x < xNum -1; x++){
                    k1 = (face*pow(xNum, 2)) + x*xNum +1;
                    k2 = k + k1;
                    // std::cout << "K1 : " << k1 << std::endl;
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
}


void Cube::attachMesh(){
    // std::cout << "Number of vertices: " << sizeof(v)/sizeof(v[0]) << std::endl;
    // // std::cerr << "v: " + sizeof(v) << std::endl;
    // for(int i =0 ; i < sizeof(v)/sizeof(v[0]); i++){
    //     std::cout << v[i] << std::endl;
    // }  
    std::cout << "procedural: " << procedural << std::endl;
    if(!procedural){

            float verts[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
 
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // std::cout << "vertex number : " << sizeof(v)/sizeof(v[0]) << std::endl;
    glGenVertexArrays(1, &meshVAO);
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glBindVertexArray(meshVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    Mesh::numVertices = 36;
    }else{

        Mesh::attachMesh();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);

        
    }
}

