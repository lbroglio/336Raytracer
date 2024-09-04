#include<vector>

#include "../world/worldObjects.hpp"
#include "../world/vectors.hpp"
#include "../config/configurator.hpp"


Vector3 castRay(Vertex startingPoint, Vertex direction){
    

}

Color** raytrace(Vertex cameraPos, int cameraPitch, int cameraYaw, Vertex lightPos, double viewLength, int imgLength, int imgWidth, Color worldColor, std::vector<Face>* faces, Configurator* config){
    // For every pixel on the screen
    for(int x=0; x < imgLength; x++){
        for(int y=0; y < imgWidth; y++){

        }

    }
}