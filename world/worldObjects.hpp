#ifndef WORLD_OBJECTS
#define WORLD_OBJECTS

#include<iostream>

#include "vectors.hpp"

/**
 * @brief Renaming of Vector3 to Vertex.
 * Represents a single point in the world;
 * 
 */
typedef Vector3 Vertex;


/**
 * @brief Holds a material read in from a .mtl file 
 * 
 */
class Material{
    public:
        /**
         * @brief Ambient lighting color of the material -- Ka field of a .mtl file
         * 
         */
        Color ambientComponent;
        /**
         * @brief Diffuse lighting color of the material -- Kd field of a .mtl file
         * 
         */
        Color diffuseComponent;
        /**
         * @brief Specular lighting color of the material -- Ks field of a .mtl file
         * 
         */
        Color specularComponent;
        /**
         * @brief The shininess of the material -- Ns field in a .mtl file
         */
        double shininess;
        /**
         * @brief Construct a new Material object with the given values
         * 
         * @param ac The ambient lighting color of this Material
         * @param dc The diffuse lighting color of this Material
         * @param dc The specular lighting color of this Material
         * @param s The shininess value of this material
         */
        Material(Color ac, Color dc, Color sc, double s): ambientComponent(ac), diffuseComponent(dc), specularComponent(sc), shininess(s){}
        /**
         * @brief Construct a new Material object -- Default constructor creates a material with the default fields for a .mtl file
         * 
         */
        Material(): ambientComponent(Color(51, 51, 51)), diffuseComponent(Color(204, 204, 204)),  specularComponent(Color(255, 255, 255)), shininess(0){}
        /**
         * @brief Equals overinding allows a material to be set from another material
         * 
         * @return This Material after updating
         */
        Material operator=(const Material& m);
    /**
     * @brief Create a string representation of a Material and pass it into an output stream
     * 
     * @param o output stream to print to
     * @param m Material to print a string representation of
     * @return The output string after the Material's representation is printed
     */
    friend std::ostream& operator<<(std::ostream& o, const Material& m);
};

/**
 * @brief Represents a normal vector read in from a .obj file
 * 
 */
class VertexNormal{
    public:
            public:
        /**
         * @brief Construct a new VertexNormal object
         * 
         * @param i The x positon of the created vertex
         * @param j The y position of the created vertex
         * @param k The z position of the created vertex
         */
        VertexNormal(double i, double j, double k): i(i), j(j), k(k){}
        /**
         * @brief Construct a new VertexNormal object
         * Default constructor sets all elements to zero
         */
        VertexNormal(): i(0), j(0), k(0){}
        /**
         * @brief i postion of this Vertex
         */
        double i;
        /**
         * @brief j postion of this Vertex
         */
        double j;
        /**
         * @brief k postion of this Vertex
         */
        double k;
};

/**
 * @brief Represents a texture vertex / vt entry in an obj file
 * 
 */
class VertexTexture{
    public:
        /**
         * @brief Construct a new VertexTexture object
         * 
         * @param u u component read in from a .obj file
         * @param v v component read in from a .obj file
         */
        VertexTexture(double u, double v): u(u), v(v){}
        /**
         * @brief Construct a new VertexTexture object
         * Default constructor sets all elements to zero
         */
        VertexTexture(): u(0), v(0){}
        /**
         * @brief u component of this Vertex
         * 
         */
        double u;
        /**
         * @brief v component of this Vertex
         * 
         */
        double v;
};


/**
 * @brief Represents a "Vertex" part of a face read in from a .obj file.
 * Holds all components in the v/vt/vn format 
 * 
 */
class ObjVertex {
    public:
        /**
         * @brief Construct a new ObjVertex object out of the three components
         * 
         * @param v The vector / v component for this ObjVertex
         * @param vt The VertexTexture / vt component for this ObjVertex
         * @param vn The VertexNormal / vn component for this ObjVertex
         */
        ObjVertex(Vertex v, VertexTexture vt, VertexNormal vn): v(v), vt(vt), vn(vn){}
        /**
         * @brief Construct a new ObjVertex object out of the interger sub components. 
         * Handles constructing the v, vt, and vn components
         * 
         * @param x The x component of the Vertex element of this ObjVertex
         * @param y The y component of the Vertex element of this ObjVertex
         * @param z The z component of the Vertex element of this ObjVertex
         * @param u The u component of the VertexTexture element of this ObjVertex
         * @param v The v component of the VertexTexture element of this ObjVertex
         * @param i The i component of the VertextNormal element of this ObjVertex
         * @param j The j component of the VertextNormal element of this ObjVertex
         * @param k The k component of the VertextNormal element of this ObjVertex
         */
        ObjVertex(double x, double y, double z, double u, double v, double i, double j, double k);
        /**
         * @brief Default constructor for an ObjVertex sets all components to zero for all elements
         */
        ObjVertex();
        /**
         * @brief Vertex element of this ObjVertex
         * 
         */
        Vertex v;
        /**
         * @brief VertexTexture element of this ObjVertex
         */
        VertexTexture vt; 
        /**
         * @brief VertexNormal element of this ObjVertex
         */
        VertexNormal vn;
};

/**
 * @brief Represnets the plane a face is on. Used for calculating intersection with rays
 * 
 */
class Plane{
    public:
        /**
         * @brief Construct a new Plane object with the given values
         * 
         * @param a a component of the new plane
         * @param b b component of the new plane
         * @param c c component of the new plane
         * @param k k component of the new plane
         */
        Plane(double a, double b, double c, double k): a(a), b(b), c(c), k(k){}
        /**
         * @brief Construct a new Plane object -- Default constructor creates a plane with all elements set to 0
         * 
         */
        Plane(): a(0), b(0), c(0), k(0){}
        double a;
        double b;
        double c;
        double k;
};

/**
 * @brief Holds the information of a triangular face within the world
 * 
 */
class Face {
    public:
        /**
         * @brief Construct a new Face object
         * Must be a triangular
         * @param v1 One of the vertices defining this face
         * @param v2 One of the vertices defining this face
         * @param v3 One of the vertices defining this face
         */
        Face(ObjVertex v1, ObjVertex v2, ObjVertex v3);
            /**
         * @brief Construct a new Face object
         * Must be a triangular
         * @param v1 One of the vertices defining this face
         * @param v2 One of the vertices defining this face
         * @param v3 One of the vertices defining this face
         * @param mat The material applied to this face
         */
        Face(ObjVertex v1, ObjVertex v2, ObjVertex v3, Material mat);
        /**
         * @brief A vertex defining this triangular face
         * 
         */
        ObjVertex v1;
        /**
         * @brief A vertex defining this triangular face
         * 
         */
        ObjVertex v2;
        /**
         * @brief A vertex defining this triangular face
         * 
         */
        ObjVertex v3;
        /**
         * @brief The material applied to this face
         * 
         */
        Material mat;
        /**
         * @brief The plane this face is on calculated from the vertex values
         * 
         */
        Plane p;


    /**
     * @brief Create a string representation of a Face and pass it into an output stream
     * 
     * @param o output stream to print to
     * @param v Face to print a string representation of
     * @return The output string after the Face's representation is printed
     */
    friend std::ostream& operator<<(std::ostream& o, const Face& f);


};


#endif