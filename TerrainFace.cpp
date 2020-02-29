#include "TerrainFace.h"


TerrainFace::TerrainFace(int subd, bool DEBUG): Mesh(false, DEBUG){
    //generate XZ plane
    float step = 1.0f/float(subd);
    int x =0;
    int y;
    glm::vec3 *p;
    for(float s = 0; s < 1.0f; s += step){
        x += 1;
        y = 0;
        for(float t = 0; t < 1.0f; t+=step){
            // glm::vec3 v(1-2*s, 0, 1 - 2*t);
            p = new glm::vec3(1 - 2*s, -1,  1-2*t);
            glm::vec3 n(0, 1, 0);
            // p->x*=2;
            // // p->z*=2;
            addVertex(*p);
            addNormal(n);
            y += 1;
        }
    }
    print();
    genIndices(x, y);
    geoMorph();
    attachMesh();
}

void TerrainFace::genIndices(int xNum, int yNum){
    int k1, k2;
    int k = yNum;
    // std::cout << "x: " << xNum << "\n\ny: " << yNum << std::endl;
        for(int x = 0; x < xNum -1; x++){
            k1 =  x*xNum +1;
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

void TerrainFace::attachMesh(){
    Mesh::createFaces();
    Mesh::attachMesh();

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    std::cout << "Reached end of vertex enabling " << std::endl;
}

void TerrainFace::geoMorph(){
    pearl = new SimplexNoise();
    double noise;
    float scale = 2;
    for(int i =0; i < vertices.size(); i++){
        glm::vec3 v = getVertex(i);
        noise = ((pearl->noise(v.x*scale, v.z*scale) +1)*0.5);
        v.y += noise;
        setVertex(i, v);
    }

}