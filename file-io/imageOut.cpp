#include<iostream>
#include<fstream>

#include"../world/vectors.hpp"


void PPMOut(std::ofstream* file, Color** outputFrom, int imgLength, int imgWidth){
    //Output the header
    *file << "P6\n";
    *file << imgLength  << ' ' << imgWidth << '\n';
    *file << "255\n";

    //Output the data
    for(int i = 0; i < imgWidth; i++){
        for(int j = 0; j < imgLength; j++){
            file->put(outputFrom[i][j].r);
            file->put(outputFrom[i][j].g);
            file->put(outputFrom[i][j].b);
        }
    }

}

