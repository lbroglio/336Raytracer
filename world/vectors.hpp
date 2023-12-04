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
        double x;
        /**
         * @brief y component of this Vector3
         * 
         */
        double y; 
        /**
         * @brief z component of this Vector3
         * 
         */
        double z;
        /**
         * @brief Construct a new Vector3 object with a given x, y, and z components
         * 
         * @param x x component of the Vector3 to create
         * @param y y component of the Vector3 to create
         * @param z z component of the Vector3 to create
         */
        Vector3(double x, double y, double z): x(x), y(y), z(z){}
        /**
         * @brief Construct a new Vector3 object -- Defautl constructor; sets all components to zero
         * 
         */
        Vector3(): x(0), y(0), z(0){}
        /**
         * @brief Takes the dot product of this Vector with another given Vector3
         * 
         * @param v The Vector3 to take the dot product with
         * @return The dot product of this Vector3 and v 
         */
        double dot(Vector3 v);
        /**
         * @brief Add override for adding together two Vectro component wise (x1 +x2 ... )
         * 
         * @param v Vectro to add to this one
         * @return New Vector created from adding these together
         */
        Vector3 operator+(const Vector3& v) const;
        /**
         * @brief += override for adding together two Vector component wise (x1 +x2 ... ) and setting this Vector 
         * to the sum
         * 
         * @param v Vectro to add to this one
         * @return This Vector after the operation
         */
        Vector3 operator+=(const Vector3& v);
        /**
         * @brief - override for subtrating two Vectors component wise (x1 - x2 ... )
         * 
         * @param v Vector to subtract from this one
         * @return New Vector created from adding these together
         */
        Vector3 operator-(const Vector3& v) const;
        /**
         * @brief -= override for subtrating two Vectors component wise (x1 - x2 ... )and setting this Vector 
         * to the difference
         * 
         * @param v Vector to subtract from this one
         * @return This Vector after the operation
         */
        Vector3 operator-=(const Vector3& v);
        /**
         * @brief * override used for performing scalar multiplication on this Vector3
         * 
         * @param s Scalar to multiply the elements of this Vector by
         * @return New Vector created after scaling
         */
        Vector3 operator*(const double& s) const;
        /**
         * @brief *= override used for performing scalar multiplication on this Vector3 and 
         * setting this vector to the result
         * 
         * @param s Scalar to multiply the elements of this Vector by
         * @return This Vector after the operation
         */
        Vector3 operator*=(const double& s);
        /**
         * @brief * override used for calculating the cross product of this Vector3 with another
         * --ORDER MATTERS FOR THIS OPERATION.
         * 
         * @param v Vector to calculate the cross product of this Vector3 with
         * 
         * @return New Vector created after finding the cross product
         */
        Vector3 operator*(const Vector3& v) const;
        /**
         * @brief *= override used for calculating the cross product of this Vector3 with another and setting this Vector
         * to the result -- ORDER MATTERS FOR THIS OPERATION.
         * 
         * @param v Vector to calculate the cross product of this Vector3 with
         * 
         * @return This Vector after setting it to the cross product
         */
        Vector3 operator*=(const Vector3& v);
        /**
         * @brief == override used for comparing to Vectors
         * 
         * @param v Vector to compare to this one
         * 
         * @return int holding the truth value of the Vectors equivalence
         */
        int operator==(const Vector3& v);
        /**
         * @brief != override used for comparing to Vectors
         * 
         * @param v Vector to compare to this one
         * 
         * @return int holding the inverted truth value of the Vectors equivalence
         */
        int operator!=(const Vector3& v);
     /**
     * @brief * override used for performing scalar multiplication on this Vector3
     * 
     * @param s Scalar to multiply the elements of this Vector by
     * @return New Vector created after scaling
     */
    friend Vector3 operator*(const double& s, const Vector3& v);
    /**
     * @brief Create a string representation of a Vector and pass it into an output stream
     * 
     * @param o output stream to print to
     * @param v Vector to print a string representation of
     * @return The output string after the Vector's representation is printed
     */
    friend std::ostream& operator<<(std::ostream& o, const Vector3& v);

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
        double& r = backingVector.x;
        /**
         * @brief Green component of this color
         * 
         */
        double& g = backingVector.y;
        /**
         * @brief Blue component of this color
         * 
         */
        double& b = backingVector.z;
        /**
         * @brief Construct a new Color object with the given red, green, and blue values
         * 
         * @param r Red component of the new color
         * @param g Green component of the new color
         * @param b Blue component of the new color
         */
        Color(double r, double g, double b): backingVector(Vector3(r, g, b)){}
        /**
         * @brief Construct a new Color object without setting any of the values
         * -- Color will be (0, 0, 0) - black
         * 
         */
        Color(){}
        /**
         * @brief Equals operator override for setting to a color reference reference. -- Sets all of the fields of this color to those of the given color
         * 
         * @return A reference to the color after it is set
         */
        Color& operator=(Color&& c);
        /**
         * @brief Equals operator override for setting to a color reference. -- Sets all of the fields of this color to those of the given color
         * 
         * @return A reference to the color after it is set
         */
        Color& operator=(const Color& c);
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