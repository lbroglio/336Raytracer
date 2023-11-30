#include<vector>
#include<cmath>

#include "../world/worldObjects.hpp"
#include "../world/vectors.hpp"

int castRay(Vertex startPos, Vector3 direction, std::vector<Face>* faces, Vertex* iPoint){
    
    // Tracks the closest intersected face so far
    int closestDist = INT32_MAX;
    // Stores the index of the closest intersected face
    int trackedIndex = -1;
    // Holds the intersection point between the currently tracked (closest) face and the ray
    Vertex trackedIPoint;

    // Find the intersection point of the Vector with all of the faces
    for(size_t i =0; i < faces->size(); i++){
        // Get a pointer to the current face
        Face* currFace = &faces->at(i);

        // Calculate the lamba (Point on the vector of the intersection point) for the current face
        // This is done with the formula lambda = -1 * ( {a, b, c} dot s + k / {a, b, c} * m)
        // a, b, c, and k are from the plane. s is the origin of the Vector. m is the direction of the Vector
        
        // The plane from the face
        Plane currPlane = currFace->p;

        Vector3 planeVector(currPlane.a, currPlane.b, currPlane.c);
        double vectorLambda = -1 * ((planeVector.dot(startPos) + currPlane.k)/ planeVector.dot(direction));

        // Use the lambda to find the coordinates of the intersection point 
        Vertex intersectionPoint = (vectorLambda * direction) + startPos;

        // At this point we know that i is on the same plane as the face but we know must filter it 
        // to check if it is actually contained within the face

        // Check if lambda is positive (or zero); Only faces in the direction of the Vector can be intersected
        if(vectorLambda < 0){
            continue;
        }

        // Check if the ray is in the bounding box of the triangle
        // This saves time over doing a complete check if it isn't necessary
        // This check is done but seeing it the intersection point's elements are smaller than the minimum / 
        // larger than the maximum of the corresponding elements of the face

        //Find the mins and maxes for the face
        int minX = std::min(std::min(currFace->v1.v.x, currFace->v2.v.x), currFace->v3.v.x);
        int minY = std::min(std::min(currFace->v1.v.y, currFace->v2.v.y), currFace->v3.v.y);
        int minZ = std::min(std::min(currFace->v1.v.z, currFace->v2.v.z), currFace->v3.v.z);

        int maxX = std::max(std::max(currFace->v1.v.x, currFace->v2.v.x), currFace->v3.v.x);
        int maxY = std::max(std::max(currFace->v1.v.y, currFace->v2.v.y), currFace->v3.v.y);
        int maxZ = std::max(std::max(currFace->v1.v.z, currFace->v2.v.z), currFace->v3.v.z);

        // Setup booleans for if the intersection is in the bounding box
        int inMinX = intersectionPoint.x >= minX;
        int inMinY = intersectionPoint.y >= minY;
        int inMinZ = intersectionPoint.z >= minZ;

        int inMaxX = intersectionPoint.x <= maxX;
        int inMaxY = intersectionPoint.y <= maxY;
        int inMaxZ = intersectionPoint.z <= maxZ;

        // If the vector is inside the bounding box
        if(inMinX && inMinY && inMinZ && inMaxX && inMaxY && inMaxZ){
            // Perform the full check to see if the intersection point is inside the face
            
            // Perform the operation three times once for f2-> f3, f1->f3, and f1->f2
            // f1, f2, and f3 and the vertices defining the face

            // Check for  f2-> f3
            Vector3 v = currFace->v2.v - currFace->v3.v;
            Vector3 a = v * (intersectionPoint - currFace->v3.v);
            Vector3 b = v * (currFace->v1.v - currFace->v3.v);
            int c = a.dot(b);
            if(c <= 0){
                continue;
            }

             // Check for  f1 -> f3
            Vector3 v = currFace->v1.v - currFace->v3.v;
            Vector3 a = v * (intersectionPoint - currFace->v3.v);
            Vector3 b = v * (currFace->v2.v - currFace->v3.v);
            int c = a.dot(b);
            if(c <= 0){
                continue;
            }

            // Check for  f1 -> f2
            Vector3 v = currFace->v1.v - currFace->v2.v;
            Vector3 a = v * (intersectionPoint - currFace->v2.v);
            Vector3 b = v * (currFace->v3.v - currFace->v2.v);
            int c = a.dot(b);
            if(c <= 0){
                continue;
            }

            // If this point is reached all checks have been passed

            // Get the distance between the intersection point and the vector's origin position
            double dist = sqrt(std::pow(startPos.x, intersectionPoint.x) + std::pow(startPos.y, intersectionPoint.y) + std::pow(startPos.z, intersectionPoint.z));

            // If the distance is less than the currently track distance set this face to the tracked face (it is the new closest)
            if(dist < closestDist){
                closestDist = dist;
                trackedIndex = i;
                trackedIPoint = intersectionPoint;
            }

        }
    }

    // Set the iPoint param to the tracked faces intersection point
    *iPoint = trackedIPoint;

    //Return the index of the first intersected face
    return trackedIndex;

}



Color** raytrace(Vertex cameraPos, int cameraPitch, int cameraYaw, Vertex lightPos, int viewLength, int viewWidth){
    // Allocate the output array
}