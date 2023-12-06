#include<vector>
#include<iostream>
#include<fstream>
#include<cmath>

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
        double vectorLambda = -1 * ((planeVector.dot(startPos) + currPlane.k) / planeVector.dot(direction));
      
        // Use the lambda to find the coordinates of the intersection point 
        Vertex intersectionPoint = (vectorLambda * direction) + startPos;

        // At this point we know that i is on the same plane as the face but we know must filter it 
        // to check if it is actually contained within the face

        // Check if lambda is positive (or zero); Only faces in the direction of the Vector can be intersected
        if(vectorLambda < 0 ){
            continue;
        }

        // Check if the ray is in the bounding box of the triangle
        // This saves time over doing a complete check if it isn't necessary
        // This check is done but seeing it the intersection point's elements are smaller than the minimum / 
        // larger than the maximum of the corresponding elements of the face

        //Find the mins and maxes for the face

        double minX = std::min(std::min(currFace->v1.v.x, currFace->v2.v.x), currFace->v3.v.x);
        double minY = std::min(std::min(currFace->v1.v.y, currFace->v2.v.y), currFace->v3.v.y);
        double minZ = std::min(std::min(currFace->v1.v.z, currFace->v2.v.z), currFace->v3.v.z);

        double maxX = std::max(std::max(currFace->v1.v.x, currFace->v2.v.x), currFace->v3.v.x);
        double maxY = std::max(std::max(currFace->v1.v.y, currFace->v2.v.y), currFace->v3.v.y);
        double maxZ = std::max(std::max(currFace->v1.v.z, currFace->v2.v.z), currFace->v3.v.z);

        // Setup booleans for if the intersection is in the bounding box
        int inMinX = !(intersectionPoint.x < minX);
        int inMinY = !(intersectionPoint.y < minY);
        int inMinZ = !(intersectionPoint.z < minZ);
    
        int inMaxX = !(intersectionPoint.x > maxX);
        int inMaxY = !(intersectionPoint.y > maxY);
        int inMaxZ = !(intersectionPoint.z > maxZ);

        // If the vector is inside the bounding box
        if(1 || (inMinX && inMinY && inMinZ && inMaxX && inMaxY && inMaxZ)){
            // Perform the full check to see if the intersection point is inside the face
            
            // Perform the operation three times once for f2-> f3, f1->f3, and f1->f2
            // f1, f2, and f3 and the vertices defining the face

            // Check for  f2-> f3
            Vector3 v = currFace->v2.v - currFace->v3.v;
            Vector3 a = v * (intersectionPoint - currFace->v3.v);
            Vector3 b = v * (currFace->v1.v - currFace->v3.v);
            double c = a.dot(b);
            if(c < 0){
                continue;
            }


             // Check for  f1 -> f3
            v = currFace->v1.v - currFace->v3.v;
            a = v * (intersectionPoint - currFace->v3.v);
            b = v * (currFace->v2.v - currFace->v3.v);
            c = a.dot(b);
            if(c < 0){
                continue;
            }

            // Check for  f1 -> f2
            v = currFace->v1.v - currFace->v2.v;
            a = v * (intersectionPoint - currFace->v2.v);
            b = v * (currFace->v3.v - currFace->v2.v);
            c = a.dot(b);
            if(c < 0){
                continue;
            }

            // If this point is reached all checks have been passed

            // Get the distance between the intersection point and the vector's origin position
            double dist = sqrt(std::pow(intersectionPoint.x - startPos.x, 2) + std::pow(intersectionPoint.y - startPos.y, 2) + std::pow(intersectionPoint.z - startPos.z, 2));

            // If the distance is less than the currently track distance set this face to the tracked face (it is the new closest) and the intersection point isn't the origin
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

/**
 * @brief Casts a reflection ray off of the given surface Handles recursion in the event of hitting mutliple reflection surfaces
 * 
 * @param intersectionPoint The point at which the reflectivesurface was hit
 * @param intersectedFaceIndex The index of the reflective surface in the faces vector
 * @param direction The direction of the ray which in intersected the reflective surface
 * @param faces Pointer to a vector containing all of the faces in the world space
 * @param currentDepth The current number of relfection rays "deep" this face is (How deep the recursion is)
 * @param maxDepth The maximum reflection/ recursion depth
 * @param lightPos The position of the worlds light source
 * @param toSet Pointer to set thbe output color to 
 * @return 1 if a reflected color has been successfully found. 0 if not
 */
int castReflection(Vertex intersectionPoint, int intersectedFaceIndex, Vector3 direction, std::vector<Face>* faces, int currentDepth, int maxDepth, Vertex lightPos, Color* toSet){
    // If this ray's reflection depth is at the maximum
    if(currentDepth == maxDepth){
        // Return 0 to indicate that no reflected color was found
        return 0;
    }

    // Calculate the direction of the reflection ray

    // Get a normal vector for the intersected face
    Face f = faces->at(intersectedFaceIndex);
    Vector3 aVector = f.v2.v -f. v1.v;
    Vector3 bVector = f.v3.v - f.v1.v;
    Vector3 faceNormal = aVector * bVector;

    // Normalize
    double magnitude = sqrt(std::pow(faceNormal.x, 2) + std::pow(faceNormal.y, 2) + std::pow(faceNormal.z, 2));
    faceNormal.x = faceNormal.x / magnitude;
    faceNormal.y = faceNormal.y / magnitude;
    faceNormal.x = faceNormal.z / magnitude;

    // Use the normal to find the reflection 
    Vector3 reflectionRay = direction - ((2 * direction.dot(faceNormal)) * faceNormal);

    // Cast the relfection ray 
    Vector3 riPoint;
    int rIndex = castRay(intersectionPoint, reflectionRay, faces, &riPoint);

    // If no face was intersected
    if(rIndex == -1){
        // Return 0 to indicate that no reflected color was found
        return 0;
    }

    // Filter the reflection if the new intersection point is too close to the origin point of the reflection ray
    if(compsWithinDist(intersectionPoint, riPoint, 0.0001)){
        // Recast the reflection with the origin face removed
        std::vector<Face> facesCopy = *faces;
        facesCopy.erase(facesCopy.begin() + rIndex);

        rIndex = castRay(intersectionPoint, reflectionRay, &facesCopy, &riPoint);

        // If no face was intersected
        if(rIndex == -1){
            // Return 0 to indicate that no reflected color was found
            return 0;
        }
    }




    // Get the material from the intersected face and check if it is reflective 
    Material intersectedMat = faces->at(rIndex).mat;

    // If another reflective material is hit recursively call
    if(intersectedMat.illumMode == 3 || intersectedMat.illumMode == 5){
        return castReflection(riPoint, rIndex, reflectionRay, faces, currentDepth+1, maxDepth, lightPos, toSet);
    }

    // If a diffuse / non reflective material was hit

    // Cast a shadow ray to ensure that the hit material has light
    Vector3 siPoint;
    // Cast a shadow ray
    int shadowFaceIndex = castRay(riPoint, lightPos, faces, &siPoint);

    // Filter valid intersection points based on proximity to starting position
    if(compsWithinDist(riPoint, siPoint, 0.0001) && shadowFaceIndex != -1){
        // If the points are ruled to be too close try again without the face included
            std::vector<Face> facesCopy = *faces;
            facesCopy.erase(facesCopy.begin() + shadowFaceIndex);

            shadowFaceIndex = castRay(riPoint, lightPos, &facesCopy, &siPoint);
    }

    // If the shadow ray returns something other than negative 1 this means there is no path from the reflected object to light
    // so 0 is returned to indicate that no reflected color was found
    if(shadowFaceIndex != -1){
        return 0;
    }

    // If the reflected object is lit 
    
    // Get its color
    Color reflectedColor = faces->at(rIndex).mat.diffuseComponent;

    // Set the color and return 1 to indicate success
    *toSet = reflectedColor;
    return 1;
}



Color** raytrace(Vertex cameraPos, int cameraPitch, int cameraYaw, Vertex lightPos, double viewLength, int imgLength, int imgWidth, Color worldColor, std::vector<Face>* faces){    
    // Allocate the output array
    Color** pixels = new Color*[imgWidth];
    for(int i=0; i < imgWidth; i++){
        *(pixels + i) = new Color[imgLength];
    }

    // Calculate the side length of the pixels by dividing the viewLength by the img imgLength
    double pixelSize = viewLength / imgLength;

    // Cast rays for every pixel
    for(int row=0; row < imgWidth; row++){
        for(int col=0; col < imgLength; col++){
            // Determine the location of the pixel in worldspace

            // Find the x and y values by ultiplying this pixels column and row shifted corresponding to the location 
            //of the center ( The location of the camera ) by the side length of the pixels
            double pixelLocX = (col - (imgLength / 2)) * pixelSize;
            double pixelLocY = ((imgWidth / 2) - row) * pixelSize;

            // The z position is one unit in front of the camera -- Rotation is handled later so for now its assumed the -z 
            // direction is "in front" of the camera
            double pixelLocZ = cameraPos.z + 1;

            // Build a direction vector from the pixels wordspace position
            Vector3 direction(pixelLocX, pixelLocY, pixelLocZ);

            // Apply the rotation of the camera
            
            // Apply yaw 
            direction.x = (direction.x * cos(cameraYaw)) + (direction.z * sin(cameraYaw));
            direction.z = ((-1 * direction.x) * sin(cameraYaw)) + (direction.z * cos(cameraYaw));

            //Apply pitch
            direction.y = (direction.y * cos(cameraYaw)) - (direction.z * sin(cameraYaw));
            direction.z = (direction.y * sin(cameraYaw)) - (direction.z * cos(cameraYaw));

            // For storing the intersection point of the ray
            Vector3 iPoint;

            // Cast the primary ray for this pixel
            int faceIndex = castRay(cameraPos, direction, faces, &iPoint);

            // If the ray intersected a face
            if(faceIndex != -1){
                Vector3 siPoint;
                // Cast a shadow ray
                int shadowFaceIndex = castRay(iPoint, lightPos, faces, &siPoint);

                // Filter valid intersection points based on proximity to starting position
                if(compsWithinDist(iPoint, siPoint, 0.0001) && shadowFaceIndex != -1){
                    // If the points are ruled to be too close try again without the face included
                    std::vector<Face> facesCopy = *faces;
                    facesCopy.erase(facesCopy.begin() + shadowFaceIndex);

                    shadowFaceIndex = castRay(iPoint, lightPos, &facesCopy, &siPoint);

                }

                double shadowScalar = 1;
                //  Set the shadow scalar if the shadow ray intersected a face other than itself
                if(shadowFaceIndex != -1){
                    shadowScalar = 0.5;
                }
                // Get the material from the intersected face
                Material mat = faces->at(faceIndex).mat;

                // Setup the Color to set the pixel to (Before any modification)
                Color pixelColor = mat.diffuseComponent;

                // Decide whether to cast a reflection ray based on the illum mode of the intersected faces material
                // by checking if the faces material is set up for relfection
                if(mat.illumMode == 3 || mat.illumMode == 5){
                    // Cast a reflection ray
                    Color reflectedColor;
                    int hasReflection = castReflection(iPoint, faceIndex, direction, faces, 0, 5, lightPos, &reflectedColor);

                    // Check if the reflection was succesful
                    if(hasReflection == 1){
                        // Set the color to the one being reflected
                        pixelColor = reflectedColor;
                        shadowScalar = 1;
                    }
                }

                // Set the the color of this pixel to be the diffuse component of the material scaled by
                // the distance of the camera to the intersection point
                double dist = sqrt(std::pow(cameraPos.x - iPoint.x, 2) + std::pow(cameraPos.y - iPoint.y, 2) + std::pow(cameraPos.z - iPoint.z, 2));
                double distScalar = std::pow(1.3,  dist);
                Color scaledColor(std::max((pixelColor.r * shadowScalar) - distScalar, 0.0), std::max((pixelColor.g * shadowScalar) - distScalar, 0.0), std::max((pixelColor.b * shadowScalar) - distScalar, 0.0));
                pixels[row][col] = scaledColor;
            }
            // If the ray did not intersect a face 
            else{
                // Set the color of this pixel to be the worldColor
                pixels[row][col] = worldColor;
            }

        }
    }

    // Return the image array 
    return pixels;

}