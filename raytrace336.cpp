#include<iostream>
#include<map>

#include "file-io/modelReaders.hpp"
#include "world/worldObjects.hpp"
#include "world/vectors.hpp"


int main(int arg, char* argv[]){
    // Read in the .mtl file specified by the second argument
    MtlReader mReader(argv[2]);
    std::map<std::string, Material> mats = mReader.readInFile();

    // Read in the .obj file specified by the first argument
    ObjReader oReader(argv[1]);
    std::vector<Face> faces = oReader.readInFile(mats);


    // Print face for checking
    for(size_t i =0; i < 3; i++){
        std::cout << faces[i] << '\n';
    }


    Vector3 tst1(1, 0, 0);
    Vector3 tst2(0, 1, 1);

    std::cout << tst1 + tst2 << '\n';
    std::cout << tst1 << '\n';
    tst1 += tst2;
    std::cout << tst1 << '\n';

    std::cout << tst1 * 3<< '\n';
    std::cout << tst1 << '\n';
    tst1 *= 3;
    std::cout << tst1 << '\n';


    std::cout << tst1 * tst2<< '\n';
    std::cout << tst1 << '\n';
    tst1 *= tst2;
    std::cout << tst1 << '\n';
    
    std::cout << std::endl;

    return 0;
}