#ifndef WORLD_OBJECTS
#define WORLD_OBJECTS

/**
 * @brief Represents a point in the world
 * 
 */
class Vertex {
    public:
        /**
         * @brief Construct a new Vertex object
         * 
         * @param x The x positon of the created vertex
         * @param y The y position of the created vertex
         * @param z The z position of the created vertex
         */
        Vertex(int x, int y, int z): x(x), y(y), z(z){}
        /**
         * @brief Construct a new Vertex object
         * Default constructor sets all elements to zero
         */
        Vertex(): x(0), y(0), z(0){}
        /**
         * @brief x postion of this Vertex
         */
        int x;
        /**
         * @brief y postion of this Vertex
         */
        int y;
        /**
         * @brief z postion of this Vertex
         */
        int z;

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
        VertexNormal(int i, int j, int k): i(i), j(j), k(k){}
        /**
         * @brief Construct a new VertexNormal object
         * Default constructor sets all elements to zero
         */
        VertexNormal(): i(0), j(0), k(0){}
        /**
         * @brief i postion of this Vertex
         */
        int i;
        /**
         * @brief j postion of this Vertex
         */
        int j;
        /**
         * @brief k postion of this Vertex
         */
        int k;
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
        VertexTexture(int u, int v): u(u), v(v){}
        /**
         * @brief Construct a new VertexTexture object
         * Default constructor sets all elements to zero
         */
        VertexTexture(): u(0), v(0){}
        /**
         * @brief u component of this Vertex
         * 
         */
        int u;
        /**
         * @brief v component of this Vertex
         * 
         */
        int v;
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
        ObjVertex(int x, int y, int z, int u, int v, int i, int j, int k);
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


};


class Material{
    public:
        int ambientComponent;
};

#endif