#include "Sphere.h"



Sphere::Sphere(int longitudeCount, int latitudeCount) : Mesh(){
 

    float longitude = 2*M_PI/longitudeCount;
    float latitude = M_PI/latitudeCount;
    float longAngle, latAngle;
    //define a sphere as a function of two angles

    std::cout << "Longitude: " << longitude << std::endl;
    std::cout << "Latitude: " << latitude << std::endl;
    //polar iteration
    for(float i = 0; i < longitude; i+= 0.1){
        std::cout << "i: " << i << std::endl;
        //equatorial iteration
        longAngle = M_PI/2 - i*longitude;
        for(float j = 0; j < latitude; j += 0.1){
            std::cout << "j: " << j << std::endl;
            latAngle = j*latitude;
            //sample our spherical parameterisation
            double x = cos(longAngle)*cos(latAngle);
            double y = cos(longAngle)*sin(latAngle);
            double z = sin(longAngle);
            // std::cout << x << y << z << std::endl;
            Mesh::addVertex(x, y, z);
        }
    }
    
    Mesh::attachMesh();
    print();
}

void Sphere::draw(){
    Mesh::draw();
}

void Sphere::print(){
    Mesh::print(true, true);
}