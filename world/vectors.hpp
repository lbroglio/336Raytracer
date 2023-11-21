#ifndef R336_VECTORS
#define R336_VECTORS




/**
 * Represents a 3 dimension Vector in the world
*/
class Vector3{
    public:
        /**
         * @brief x component of this Vector3
         * 
         */
        int x;
        /**
         * @brief y component of this Vector3
         * 
         */
        int y; 
        /**
         * @brief z component of this Vector3
         * 
         */
        int z;
        /**
         * @brief Construct a new Vector3 object with a given x, y, and z components
         * 
         * @param x x component of the Vector3 to create
         * @param y y component of the Vector3 to create
         * @param z z component of the Vector3 to create
         */
        Vector3(int x, int y, int z): x(x), y(y), z(z){}
        /**
         * @brief Construct a new Vector3 object -- Defautl constructor; sets all components to zero
         * 
         */
        Vector3(): x(0), y(0), z(0){}
};

/**
 * @brief A Color stored as an red, green, and blue integer value
 * 
 */
class Color{
    public:
        /**
         * @brief Red component of this color
         * 
         */
        int& r = backingVector.x;
        /**
         * @brief Green component of this color
         * 
         */
        int& g = backingVector.y;
        /**
         * @brief Blue component of this color
         * 
         */
        int& b = backingVector.z;
        /**
         * @brief Construct a new Color object with the given red, green, and blue values
         * 
         * @param r Red component of the new color
         * @param g Green component of the new color
         * @param b Blue component of the new color
         */
        Color(int r, int g, int b): backingVector(Vector3(r, g, b)){}
        /**
         * @brief Construct a new Color object without setting any of the values
         * -- Color will be (0, 0, 0) - black
         * 
         */
        Color(){}
        /**
         * @brief Equals operator override. -- Sets all of the fields of this color to those of the given color
         * 
         * @return A reference to the new color
         */
        Color& operator=(Color&& c);
        /**
         * @brief Constuctor used for creating a color from another 
         *  
         */
        Color(const Color& c): backingVector(Vector3(c.r, c.g, c.b)){}
    private:
        /**
         * @brief Vector 3 object used to back this color
         * 
         */
        Vector3 backingVector;
};

#endif