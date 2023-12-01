#include<vector>

#include "../world/worldObjects.hpp"
#include "../world/vectors.hpp"

/**
 * @brief Function to cast a ray. Draws a ray from the given point in the indicated direction and returns the index 
 * of the first Face (first meaning the Face closest to it in the world) it intersects with in the given list (if any).
 * 
 * @param startPos The point at which the ray starts / is cast from
 * @param direction Vector representing the direction the ray is cast in
 * @param faces A list of faces in the world to check for intersections with the ray
 * @param iPoint Pointer to a Vertex object used to return the intersection point between the cast ray and the face it intersects
 * @return The index of the first Face in the list face the ray intersects or -1 if no face is intersected.
 */
int castRay(Vertex startPos, Vector3 direction, std::vector<Face>* faces, Vertex* iPoint);

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
 * @return An array of Color objects represeting the rendered image
 */
Color** raytrace(Vertex cameraPos, int cameraPitch, int cameraYaw, Vertex lightPos, double viewLength, int imgLength, int imgWidth,Color worldColor, std::vector<Face>* faces);