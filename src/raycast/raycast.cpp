#include<vector>

#include "../world/worldObjects.hpp"
#include "../world/vectors.hpp"
#include "../config/configurator.hpp"
#include"../util/util.cpp"
#include "raycast.hpp"


RayCast castRay(Vertex startingPoint, Vertex direction, std::vector<Face>* faces){
    // Save intersections
    std::vector<RayCast> intersections;

    // Check intersection with all faces
    for(Face f : *faces){
        Vector3 pVector(f.p.a, f.p.b, f.p.c);
        // Calculate the distance along the ray at which the ray intersects this face (lambda)
        float numerator = pVector.dot(startingPoint) + f.p.k;
        float denominator = pVector.dot(direction);
        float lambda = -1 * (numerator / denominator);

        // Calculate intersection point
        Vertex iPoint = (lambda * direction) + startingPoint;

        // Filter if intersection point is valid

        // Only continue if lambda is positive 
        if(lambda >= 0){
            // TODO Improve efficiency by checking for intersection in the bounding rectangle first 


            // Check if the intersection point is inside the face 

            // Check if i and v1 are on the same side of of v2->v3
            Vector3 v = f.v2.v - f.v3.v;
            Vector3 a = v * (iPoint - f.v3.v);
            Vector3 b = v * (iPoint - f.v3.v);
            float c1 = a.dot(b);

            // Check if i and v2 are on the same side of of v1->v3
            Vector3 v = f.v1.v - f.v3.v;
            Vector3 a = v * (iPoint - f.v3.v);
            Vector3 b = v * (iPoint - f.v3.v);
            float c2 = a.dot(b);

            // Check if i and v3 are on the same side of of v1->v2s
            Vector3 v = f.v1.v - f.v2.v;
            Vector3 a = v * (iPoint - f.v2.v);
            Vector3 b = v * (iPoint - f.v2.v);
            float c3 = a.dot(b);

            // If the iPoint is within the triangle (c1-3 are all > 0)
            if(c1 >= 0 && c2 >= 0 && c3 >= 0){
                intersections.push_back(RayCast(true, iPoint, f));
            }
        }
    }

    // If no intersections are found return a false RayCast object
    if(intersections.size() == 0){
        return RayCast(false);
    }

    // Otherwise select intersection closest to camera
    RayCast closestIntersection(false);
    float closestDist = __FLT_MAX__;

    for(RayCast r : intersections){
        // Calculate the distance from the camers to this intersection point
        float dist = dist3D(r.iPoint, startingPoint);

        // If this distance is less than the current saved least dist
        if(dist < closestDist){
            // Set this intersection as the one to retur 
            closestDist = dist;
            closestIntersection = r;
        }
    }

    return closestIntersection;
}

Color** raytrace(Vertex cameraPos, int cameraPitch, int cameraYaw, Vertex lightPos, double viewLength, int imgLength, int imgWidth, Color worldColor, std::vector<Face>* faces, Configurator* config){
    // For every pixel on the screen
    for(int x=0; x < imgLength; x++){
        for(int y=0; y < imgWidth; y++){

        }

    }
}