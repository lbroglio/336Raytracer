#include <stdexcept>

#include "worldObjects.hpp"

ObjVertex::ObjVertex(int x, int y, int z, int u, int v, int i, int j, int k){
    // Create a Vertex component for this ObjVertex
    this->v = Vertex(x, y, z);

    // Create a VertexTexture component for this ObjVertex
    this->vt = VertexTexture(u, v);

    // Create a VertexNormal component for this ObjVertex
    this->vn = VertexNormal(i, j, k);
}

ObjVertex::ObjVertex(){
    *this = ObjVertex(0, 0, 0, 0, 0, 0, 0, 0);
}

Face::Face(ObjVertex v1, ObjVertex v2, ObjVertex v3){
    // Determine if a valid triangle is given 
    int a = 0;
    // Check if all three points lie on a plane (One of there all components if equal)
    if(v1.v.x == v2.v.x && v2.v.x == v3.v.x){
        // Check that it is a valid triangle
        a = v1.v.y * (v2.v.z - v3.v.z) + v2.v.y * (v3.v.z - v1.v.z) + v3.v.y * (v1.v.z - v2.v.z);
    }
    else if(v1.v.y == v2.v.y && v2.v.y == v3.v.y){
        // Check that it is a valid triangle
        a = v1.v.x * (v2.v.z - v3.v.z) + v2.v.x * (v3.v.z - v1.v.z) + v3.v.x * (v1.v.z - v2.v.z);
        
    }
    else if(v1.v.z == v2.v.z && v2.v.z == v3.v.z){
        // Check that it is a valid triangle
        a = v1.v.y * (v2.v.x - v3.v.x) + v2.v.y * (v3.v.x - v1.v.x) + v3.v.y * (v1.v.x - v2.v.x);
    }

    // If the vertices do not form a triangle because the side lengths are wrong or they all line on differnet planes
    if(a == 0){
        throw std::invalid_argument("v1, v2, and v3 must form a valid triangle");
    }
    
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}
