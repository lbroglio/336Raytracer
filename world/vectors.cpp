#include<iostream>
#include<cmath>

#include "vectors.hpp"

Color& Color::operator=(Color&& c){
    r = c.r;
    g = c.g;
    b = c.b;

    return *this;
}

Color& Color::operator=(const Color& c){
    r = c.r;
    g = c.g;
    b = c.b;

    return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const{
    double summedX = this->x + v.x;
    double summedY = this->y + v.y;
    double summedZ = this->z + v.z;

    return Vector3(summedX, summedY, summedZ);
}


Vector3 Vector3::operator+=(const Vector3& v){
    return (*this = *this + v); 
}

Vector3 Vector3::operator*(const double& s) const{
    double prodX = this->x * s;
    double prodY = this->y * s;
    double prodZ = this->z * s;

    return Vector3(prodX, prodY, prodZ);
}


Vector3 Vector3::operator*=(const double& s){
    return (*this = *this * s); 
}


Vector3 Vector3::operator-(const Vector3& v) const{
    return *this + (v * -1);
}

Vector3 Vector3::operator-=(const Vector3& v){
    return (*this = *this - v); 
}

Vector3 operator*(const double& s, const Vector3& v){
    return v * s;
}




Vector3 Vector3::operator*(const Vector3& v) const{
    double crossX = (this->y * v.z) - (this->z * v.y);
    double crossY = (this->z * v.x) - (this->x * v.z);
    double crossZ = (this->x * v.y) - (this->y * v.x);

    return Vector3(crossX, crossY, crossZ);
}

Vector3 Vector3::operator*=(const Vector3& v){
    return (*this = *this * v); 
}


std::ostream& operator<<(std::ostream& o, const Vector3& v){
    o << "Vector:{";
    o << "x: " << v.x << ", y: " << v.y << ", z: " << v.z;
    o <<"}\n";
    
    return o;
}


double Vector3::dot(Vector3 v){
   return (this->x * v.x) + (this->y * v.y) +  (this->z * v.z);
}

int Vector3::operator==(const Vector3& v){
    return (this->x == v.x && this->y == v.y && this->z == v.z); 
}

int Vector3::operator!=(const Vector3& v){
    return !(*this == v); 
}


int vecsWithinDist(Vector3 v1, Vector3 v2, double dist){
    double vecDist = sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2) + std::pow(v1.z - v2.z, 2));

    // Check that the two vectors are more than dist apart
    return vecDist <= dist;
}
