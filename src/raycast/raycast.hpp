#include<vector>

#include "../world/worldObjects.hpp"
#include "../world/vectors.hpp"
#include "../config/configurator.hpp"

/**
 * @brief Peforms the raytrace operation on the model. Casts all the primary, shadow, and reflection rays.
 * uses this information to set the pixel colors and returns the rendered image as an allocated array of Color objects
 * which holds the Color of each pixel in the image. 
 * The length of the amount of world space to capture is given and the width/height of the space is dependent on
 * the width (number of pixels) of the image and the size of the pixels
 * 
 * @param cameraPos The coordinates of the viewpoint / camera in the world as a Vertex object
 * @param cameraPitch The pitch rotation of the camera
 * @param cameraYaw  The yaw rotation of the camera
 * @param lightPos The coordinates of the light source in the world as a Vertex object
 * @param viewLength The length of the view in world coordinates. The width is dependent on the size of the pixels
 * and how many pixels high the image is 
 * @param imgLength The number of pixels long the image being output is 
 * @param imgWidth The number of pixels wide (high) the image being output is
 * @param worldColor The color to assign pixels for which the ray didn't intersect a face
 * @param faces Pointer to a std::vector of faces containing the list of faces in the world
 * @param config Object which holds user set configurations of the program. 
 * @return An array of Color objects represeting the rendered image
 */
Color** raytrace(Vertex cameraPos, int cameraPitch, int cameraYaw, Vertex lightPos, double viewLength, int imgLength, int imgWidth,Color worldColor, std::vector<Face>* faces, Configurator* config);