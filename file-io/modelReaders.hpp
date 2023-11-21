#ifndef MODEL_READERS
#define MODEL_READERS


#include<string>
#include<vector>
#include<map>

#include "../world/worldObjects.hpp"


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
        ObjReader(std::string path): targetPath(path){}
        /**
         * @brief Construct a new Obj Reader object
         * 
         * @param path The path to the file to read in as a c style char* 
         */
        ObjReader(char* path): targetPath(std::string(path)){}
        /**
         * @brief Read in the obj file this ObjReader is pointing to and return its contents as a vector of Face objects
         * 
         * @return A vector of face objects read in from the .obj file
         */
        std::vector<Face> readInFile();
        std::vector<Face> readInFile(std::map<std::string, Material> materials);

    private:
        /**
         * @brief The path to the file to read in 
         */
        std::string targetPath;
};

/**
 * @brief Object which reads a .mtl file into the program and returns it as a map of Material objects associated with there names
 * 
 */
class MtlReader {
    public:
        /**
         * @brief Construct a new MtlReader object
         * 
         * @param path The path to the file to read in as a c++ string object
         */
        MtlReader(std::string path): targetPath(path){}
        /**
         * @brief Construct a new MtlReader object
         * 
         * @param path The path to the file to read in as a c style char* 
         */
        MtlReader(char* path): targetPath(std::string(path)){}
        /**
         * @brief Read in the mtl file this MtlReader is pointing to and return its contents as a map of Material Objects
         * 
         * @return A map storing the material objects read in associated with there names
         */
        std::map<std::string, Material> readInFile();

    private:
        /**
         * @brief The path to the file to read in 
         */
        std::string targetPath;
};


#endif