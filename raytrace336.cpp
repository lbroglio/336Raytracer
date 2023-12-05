#include<iostream>
#include<fstream>
#include<map>

#include "file-io/modelReaders.hpp"
#include "file-io/imageOut.hpp"
#include "world/worldObjects.hpp"
#include "world/vectors.hpp"
#include "raycast/raycast.hpp"


int main(int arg, char* argv[]){

    // Read in the .mtl file specified by the second argument
    MtlReader mReader(argv[2]);
    std::map<std::string, Material> mats = mReader.readInFile();

    // Read in the .obj file specified by the first argument
    ObjReader oReader(argv[1]);
    std::vector<Face> faces = oReader.readInFile(mats);

    /*
    std::ofstream logFile("log.txt");
    for(size_t i =0; i < faces.size(); i++){
        logFile << faces[i] << "-----\n";
    }
    logFile.close()
    */

    // Render the image
    Color** pixels;
    pixels = raytrace(Vector3(0, 1, -5), 0, 0, Vector3(0, 10, -3), 8, 1080, 1080, Color(135, 206, 235), &faces);

    // Output the pixels as an image file
    
    // Open the output image
    std::ofstream outFile("renderedImage.ppm");

    // Output the rendered image
    PPMOut(&outFile, pixels, 1080, 1080);

    //Close the file 
    outFile.close();

    return 0;
}