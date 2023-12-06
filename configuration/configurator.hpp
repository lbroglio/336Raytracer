#ifndef R336_CONFIG
#define R336_CONFIG



#include"../world/vectors.hpp"



struct Configurator{
    Color worldColor = Color(255, 255, 255);
    Vector3 cameraPos = Vector3(0, 0, -1);
    Vector3 lightPos = Vector3(0, 10, 0);
    int imageLength = 1080;
    int imageWidth = 1080;
    int maximumReflectionDeph = 5;
    double shadowScaleBase = 1.3;
};

#endif