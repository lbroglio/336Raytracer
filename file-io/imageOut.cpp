#include<iostream>
#include<fstream>

#include"../world/vectors.hpp"


std::ofstream& PPMOut(std::ofstream& file, Color** outputFrom, int imgLength, int imgWidth){
    //Output the header
    file << "P6\n";
    file << imgLength  << ' ' << imgWidth << '\n';
    file << "255\n";

    //Output the data
    for(int i = 0; i < imgLength; i++){
        for(int j = 0; j < imgWidth; j++){
            file.put(outputFrom[i][j].r);
            file.put(outputFrom[i][j].g);
            file.put(outputFrom[i][j].b);
        }
    }

    return file;
}

