#ifndef R336_GPURENDER
#define R336_GPURENDER

#include<vector>

#include "../world/worldObjects.hpp"

/**
 * @brief Render the models read in by the program using the traditional graphics pipeline and OpenGL.
 * Used to test the raytracers model reading independently of its rendering components.
 * 
 * @param faces List of face objects to render
 * @param worldColor The background color 
 * @param cameraPos Location of the camera in the world
 * @param cameraPitch Up-down rotation of the camera
 * @param cameraYaw Side-side rotation of the camera
 * @return true - The model was rendered without issue
 * @return false - An error occured while rendering the model
 */
bool renderWithGPU(std::vector<Face>* faces, Color worldColor, Vertex cameraPos, int cameraPitch, int cameraYaw);

#endif