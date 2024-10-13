#include<iostream>
#include<fstream>
#include<map>

#include "file-io/modelReaders.hpp"
#include "file-io/imageOut.hpp"
#include "world/worldObjects.hpp"
#include "world/vectors.hpp"
#include "raycast/raycast.hpp"
#include "config/configurator.hpp"


int main(int argc, char* argv[]){
    // Setup program configurations
    Configurator config;

    // If a configuration file was given on the command line use it to set program configs
    if(argc > 3){
        ConfigReader cReader = ConfigReader(argv[3]);

        config =  cReader.readInFile();
    }

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
    logFile.close();
    */

    // Render the image
    Color** pixels;
    pixels = raytrace(config.cameraPos, 0, 0, config.lightPos, 8, config.imageLength, config.imageWidth, config.worldColor, &faces, &config);

    // Output the pixels as an image file
    
    // Open the output image
    std::ofstream outFile("renderedImage.ppm");

    // Output the rendered image
    PPMOut(&outFile, pixels, config.imageLength, config.imageWidth);

    //Close the file 
    outFile.close();

    // Call python script to convert output to png
    system("python convertImage.py renderedImage.ppm");

    // Check if the .png file exists 
    std::ifstream checkFile("renderedImage.png");
    if(!checkFile.is_open()){
        // If it doesn't try using the python3 command
        system("python3 convertImage.py renderedImage.ppm");
        checkFile = std::ifstream("renderedImage.png");
    }

    // Check if the .png file exists 
    if (checkFile.is_open()) {
        // If the file exists delete the ppm 
        remove("renderedImage.ppm");
        checkFile.close();
    }

    // Memory clean up
    for(int i=0; i < config.imageWidth; i++){
        delete[] pixels[i];
    }
    delete[] pixels;



    return 0;
}