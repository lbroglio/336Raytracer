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
 * @return The index of the first Face in the list face the ray intersects or -1 if no face is intersected.
 */
int castRay(Vertex startPos, Vector3 direction, std::vector<Face>* faces);