#include"../world/worldObjects.hpp"
#include"util.hpp"
#include<cmath>

float dist3D(Vertex v1, Vertex v2){
    return sqrt(std::pow(v2.x - v1.x, 2) + std::pow(v2.y - v1.y, 2) + std::pow(v2.z - v1.z, 2));
}