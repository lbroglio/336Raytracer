#include<string>
#include<vector>


/**
 * @brief Object which reads a .obj file into the program and returns it as a list of face objects
 * 
 */
class ObjReader {
    public:
        /**
         * @brief Construct a new ObjReader object
         * 
         * @param path The path to the file to read in as a c++ string object
         */
        ObjReader(std::string path);
        /**
         * @brief Construct a new Obj Reader object
         * 
         * @param path The path to the file to read in as a c style char* 
         */
        ObjReader(char* path);

    private:
        /**
         * @brief The path to the file to read in 
         */
        std::string targetPath;
};