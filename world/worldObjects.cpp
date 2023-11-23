#include <stdexcept>
#include<iostream>

#include "worldObjects.hpp"

ObjVertex::ObjVertex(double x, double y, double z, double u, double v, double i, double j, double k){
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
    // TODO - REWORK TRIANGLE CHECKING CODE
    /*
    // Determine if a valid triangle is given 
    int a = 0;
    // Check if all three points lie on a plane (One of there all components if equal)
    if(v1.v.x == v2.v.x && v2.v.x == v3.v.x){
        // Check that it is a valid triangle
        std::cout << "checkFired" << '\n';
        a = v1.v.y * (v2.v.z - v3.v.z) + v2.v.y * (v3.v.z - v1.v.z) + v3.v.y * (v1.v.z - v2.v.z);
    }
    else if(v1.v.y == v2.v.y && v2.v.y == v3.v.y){
        // Check that it is a valid triangle
        std::cout << "checkFired" << '\n';
        a = v1.v.x * (v2.v.z - v3.v.z) + v2.v.x * (v3.v.z - v1.v.z) + v3.v.x * (v1.v.z - v2.v.z);
        
    }
    else if(v1.v.z == v2.v.z && v2.v.z == v3.v.z){
        // Check that it is a valid triangle
        std::cout << "checkFired" << '\n';
        a = v1.v.y * (v2.v.x - v3.v.x) + v2.v.y * (v3.v.x - v1.v.x) + v3.v.y * (v1.v.x - v2.v.x);
    }
    else{
        std::cout << "Np CHeck fired" << '\n';
    }

    // If the vertices do not form a triangle because the side lengths are wrong or they all line on differnet planes
    if(a == 0){
        throw std::invalid_argument("v1, v2, and v3 must form a valid triangle");
    }
    */

    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}

Material Material::operator=(const Material& m){
    ambientComponent = m.ambientComponent;
    diffuseComponent = m.diffuseComponent;
    specularComponent = m .specularComponent;
    shininess = m.shininess;

    return *this;
}


std::ostream& operator<<(std::ostream& o, const Material& m){
    o << "Material:{\n";
    o << "\t Ambient component: (" << m.ambientComponent.r << ", " << m.ambientComponent.g << ", " << m.ambientComponent.b << ")\n";
    o << "\t Diffuse component: (" << m.diffuseComponent.r << ", "<<  m.diffuseComponent.g << ", " << m.diffuseComponent.b << ")\n";
    o << "\t Specular component: (" << m.specularComponent.r << ", "<<  m.specularComponent.g << ", " << m.specularComponent.b << ")\n";
    o << "\t Shininess Value: " << m.shininess << "\n";
    o << "}\n";

    return o;

}


std::ostream& operator<<(std::ostream& o, const Vertex& v){
    o << "Vertex:{\n";
    o << "\tx: " << v.x << ", y: " << v.y << ", z: " << v.z;
    o <<"}\n";
    
    return o;
}


std::ostream& operator<<(std::ostream& o, const Face& f){
    o << "Face:{\n";
    o << "\tVertices[\n" << f.v1.v << f.v2.v << f.v3.v << "]\n";
    o << "\tMaterial: " << f
    o << "}\n";

    return o;
}