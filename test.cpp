#include<iostream>
#include<stdexcept>

#include"world-objects/worldObjects.hpp"


void testFaceTriangleDetection(){

    // Test creating a valid right triangle 
    int caughtFlag = 1;
    try{
        ObjVertex a1 = ObjVertex(0, -1, 1, 0, 0, 0, 0, 0);
        ObjVertex a2 = ObjVertex(0, -1, 2, 0, 0, 0, 0, 0);
        ObjVertex a3 = ObjVertex(1, -1, 2, 0, 0, 0, 0, 0);

        Face(a1, a2, a3);
    }
    catch(const std::invalid_argument& e){
        std::cout << "Test 1: Failed\n" << std::endl; 
        caughtFlag = 0;
    }

    if(caughtFlag == 1){
        std::cout << "Test 1: Passed\n" << std::endl; 
    }

    // Test creating a valid triangle 
    caughtFlag = 1;
    try{
        ObjVertex b1 = ObjVertex(0, 0, 0, 0, 0, 0, 0, 0);
        ObjVertex b2 = ObjVertex(0, 0, 4, 0, 0, 0, 0, 0);
        ObjVertex b3 = ObjVertex(0, 2, 2, 0, 0, 0, 0, 0);

        Face(b1, b2, b3);
    }
    catch(const std::invalid_argument& e){
        std::cout << "Test 2: Failed\n" << std::endl; 
        caughtFlag = 0;
    }

    if(caughtFlag == 1){
        std::cout << "Test 2: Passed\n" << std::endl; 
    }

    // Test creating an invlaid triangle because the points don't share a plane
    caughtFlag = 1;
    try{
        ObjVertex c1 = ObjVertex(1, 2, 3, 0, 0, 0, 0, 0);
        ObjVertex c2 = ObjVertex(4, 5, 6, 0, 0, 0, 0, 0);
        ObjVertex c3 = ObjVertex(7, 8, 9, 0, 0, 0, 0, 0);

        Face(c1, c2, c3);
    }
    catch(const std::invalid_argument& e){
        std::cout << "Test 3: Passed\n" << std::endl; 
        caughtFlag = 0;
    }

    if(caughtFlag == 1){
        std::cout << "Test 3: Failed\n" << std::endl; 
    }


    // Test creating an invaldi triangle because all of the points are in one line
    caughtFlag = 1;
    try{
        ObjVertex d1 = ObjVertex(1, -1, 0, 0, 0, 0, 0, 0);
        ObjVertex d2 = ObjVertex(2, -1, 0, 0, 0, 0, 0, 0);
        ObjVertex d3 = ObjVertex(3, -1, 0, 0, 0, 0, 0, 0);

        Face(d1, d2, d3);
    }
    catch(const std::invalid_argument& e){
        std::cout << "Test 4: Passed\n" << std::endl; 
        caughtFlag = 0;
    }

    if(caughtFlag == 1){
        std::cout << "Test 4: Failed\n" << std::endl; 
    }



}


int main(int argc, char* argv[]){
    testFaceTriangleDetection();
}