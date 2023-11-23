#include<vector>
#include<map>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<cmath>

#include "modelReaders.hpp"
#include "../world/worldObjects.hpp"
#include "../world/vectors.hpp"


/**
 * @brief Read characters in from a file until a new line or EOF character is encountered;
 * Return the read in chars as a string (excluding the newline or EOF chars)
 * 
 * @param readFrom The file stream to read from
 * @return The characters int he file between the current location and the next newline or EOF character as a string
 */
std::string readLine(std::ifstream* readFrom){
    // Store the line of the file read in
    std::string line = "";

    // Read the file character by character until a new line (or the EOF) is encountered
    while(readFrom->peek() != '\n' && readFrom->peek() != EOF){
        // Read in the next character
        char next = readFrom->get();

        // Add it to the string 
        line += next;
    }

    // Move past the next character in the file 
    readFrom->get();

    //Return the read in line
    return line;
}

/**
 * @brief Count the number of times a given character appears in a given string
 * 
 * @param countFrom The string to count the occurences of a character within
 * @param toCount The character to count the occurences of 
 * @return 
 */
int countChar(std::string countFrom, char toCount){
    // Var to track occurences of toCoutn
    int numOccurences = 0;
    
    // Loop throug every character in countFrom
    for(size_t i=0; i< countFrom.length(); i++){
        char currChar = countFrom[i];

        // If the current char is the target char increment the nubmer of occurences
        if(currChar == toCount){
            numOccurences++;
        }
    }

    return numOccurences;
}

/**
 * @brief Split a string into an array of subs strings divided by a given character -- The instances of the given character
 * will not be included in the substrings -- 
 * Allocates memory for the the array
 * 
 * @param toSplit The string to split up by whitespace
 * 
 * @return An allocated array of sub strings
 * 
 */
std::string* splitString(std::string toSplit, char splitAt){
    // Find number of spaces in the string
    int numSpaces = countChar(toSplit, splitAt);

    // Create the array to store the split string
    std::string* splitString = new std::string[numSpaces + 1];

    // Tracks the current index to add a substring to 
    int indexTracker = 0;

    // Hold a section of the string 
    std::string subStr = "";

    // Loop through the string character by character
    for(size_t i = 0; i < toSplit.length(); i++){
        char currChar = toSplit[i];

        // If the current character is a space save the current substring and reset to read in another substring
        if(currChar == splitAt){
            splitString[indexTracker] = subStr;
            subStr = "";
            indexTracker++;
        }
        // if the current character isn't a space
        else{
            subStr += currChar;
        }
    }

    //Add the final substring to the list
    splitString[indexTracker] = subStr;

    return splitString;
}

std::map<std::string, Material> MtlReader::readInFile(){
    // Open the target file for reading 
    std::ifstream mtlFile(targetPath);

    // Map to hold read in materials
    std::map<std::string, Material> matMap;

    // Vars to hold fields read in from the .mtl file
    Color Ka(51, 51, 51);
    Color Kd(204, 204, 204);
    Color Ks(255, 255, 255);
    double shininess = 0;
    std::string mtlName = " ";

    // Read lines from the file until the end
    while(mtlFile.peek() != EOF){
        // Read the next line from the file
        std::string line = readLine(&mtlFile);

        // Split the line up by spaces
        std::string* splitStr = splitString(line, ' ');

        // Decide how to parse the line based on the first substring
        // Parse as an ambient lighting component
        if(splitStr[0] == "Ka"){
            // Parse the three components as doubles 
            double c1 = atof(splitStr[1].c_str());
            double c2 = atof(splitStr[2].c_str());
            double c3 = atof(splitStr[3].c_str());

            // Convert the components to integers on a 0 - 255 scale;
            int c1Int = std::round(c1 * 255);
            int c2Int = std::round(c2 * 255);
            int c3Int = std::round(c3 * 255);

            // Use the compoents to set Ka
            Ka = Color(c1Int, c2Int, c3Int);
        }
        // Parse as a diffuse lighting component
        else if(splitStr[0] == "Kd"){
            // Parse the three components as doubles 
            double c1 = atof(splitStr[1].c_str());
            double c2 = atof(splitStr[2].c_str());
            double c3 = atof(splitStr[3].c_str());

            // Convert the components to integers on a 0 - 255 scale;
            int c1Int = std::round(c1 * 255);
            int c2Int = std::round(c2 * 255);
            int c3Int = std::round(c3 * 255);

            // Use the compoents to set Kd
            Kd = Color(c1Int, c2Int, c3Int);
        }
        // Parse as a specular lighting component
        else if(splitStr[0] == "Ks"){
            // Parse the three components as doubles 
            double c1 = atof(splitStr[1].c_str());
            double c2 = atof(splitStr[2].c_str());
            double c3 = atof(splitStr[3].c_str());

            // Convert the components to integers on a 0 - 255 scale;
            int c1Int = std::round(c1 * 255);
            int c2Int = std::round(c2 * 255);
            int c3Int = std::round(c3 * 255);

            // Use the compoents to set Ks
            Ks = Color(c1Int, c2Int, c3Int);
        }
        // Parse as the shiniess value
        else if(splitStr[0] == "Ns"){
            // Parse the shininess as a double and use it to set the shininess var
           shininess = atof(splitStr[1].c_str());
        }
        // If a new material is being indicated
        else if(splitStr[0] == "newmtl"){
            // If a material has been started
            if(mtlName != " "){
                // Save the currently being read in material and reset
                Material parsedMat(Ka, Kd, Ks, shininess);

                // Associate the newly created material with its name in the map
                matMap.insert({mtlName, parsedMat});
            }


            // Reset the values for reading a new material
            Ka = Color(51, 51, 51);
            Kd = Color(204, 204, 204);
            Ks = Color(255, 255, 255);
            shininess = 0;
            mtlName = splitStr[1];
        }

        // Free the memory from the list of strings
        delete[] splitStr;
    }

    // Save the last read in material
    Material parsedMat(Ka, Kd, Ks, shininess);
    matMap.insert({mtlName, parsedMat});

    // Return the mapping of materials
    return matMap;
}


 std::vector<Face> ObjReader::readInFile(std::map<std::string, Material> materials){
    // Open the target file for reading 
    std::ifstream mtlFile(targetPath);

    //Vector to store the read in faces
    std::vector<Face> faces; 

    // Vectors to hold lists of the points read in from the .obj file 
    std::vector<Vertex> vList;
    std::vector<VertexTexture> vtList;
    std::vector<VertexNormal> vnList;
    
    // Hold the current material to be applied to a created face
    Material currMat;

    // Read lines from the file until the end
    while(mtlFile.peek() != EOF){
        // Read the next line from the file
        std::string line = readLine(&mtlFile);

        // Split the line up by spaces
        std::string* splitStr = splitString(line, ' ');

        // Decide how to parse the line based on the first substring
        // Parse as an indicator for a new object
        if(splitStr[0] == "o"){
            // Reset the vertex arrays to be empty 
            vList = std::vector<Vertex>();
            vtList = std::vector<VertexTexture>();
            vnList = std::vector<VertexNormal>();

            // Reset the material to be the default material
            currMat = Material();

        }
        // Parse as a vertex (v field)
        else if(splitStr[0] == "v"){
            // Read the three components of the vertex from the line
            double xComp = atof(splitStr[1].c_str());
            double yComp = atof(splitStr[2].c_str());
            double zComp = atof(splitStr[3].c_str());

            // Create a Vertex object and save it
            Vertex readIn(xComp, yComp, zComp);
            vList.push_back(readIn);
        }
        // Parse as a texture vertex (vt field)
        else if(splitStr[0] == "vt"){
            // Read the two components of the texture vertex from the line
            double uComp = atof(splitStr[1].c_str());
            double vComp = atof(splitStr[2].c_str());

            // Create a VertexTexture object and save it
            VertexTexture readIn(uComp, vComp);
            vtList.push_back(readIn);
        }
        // Parse as a Vertex normal (vn field)
        else if(splitStr[0] == "vn"){
            // Read the three components of the vertex normal from the line
            double iComp = atof(splitStr[1].c_str());
            double jComp = atof(splitStr[2].c_str());
            double kComp = atof(splitStr[3].c_str());

            // Create a VertexNormal object and save it
            VertexNormal readIn(iComp, jComp, kComp);
            vnList.push_back(readIn);
        }
        // Parse as an indicator to swtich the material being used
        else if(splitStr[0] == "usemtl"){
            // Read the name of the new material
            std::string matName = splitStr[1];

            // Check if the material name is in the provided map
            if(materials.count(matName)){
                currMat = materials[matName];
            }
            // If the material is unknown switch to the default color
            else{
                currMat = Material();
            }
        }
        // Parse as a Face (f field)
        else if(splitStr[0] == "f"){
            // Send an error to the console if the face isn't a triangle

            // Check if the line has more than three entries (exlcuding the f indicator)
            // This is done by first checking if the length is long enough to have the extra entries
            if(countChar(line, ' ') + 1 > 4){
                // If the line is long enough through an error if the extra entries are empty
                // This is to prevent a failure being caused by extraneous spaces
                for(int i= 4; i < countChar(line, ' ') + 1; i++){
                    std::string currEntry = splitStr[1];

                    int entryLen = currEntry.length();
                    // If this entry is empty or only contains spaces
                    if(currEntry != "" && entryLen  != countChar(currEntry, ' ')){
                        std::cerr << "Error: " << targetPath << "must only contain triangular faces." << std::endl;
                        exit(1);
                    }
                }
            }

                // Read for every entry in the vertexes of the triangle

                // List to store the three created vertices
                ObjVertex faceEls[3];
                
                //For every entry
                for(int i =0; i<3; i++){
                   
                    std::string entry = splitStr[i];
                    // Check if the entry has a texture and normal vertex or if it just a vertex
                    // by checking if the entry nas / characters
                    if(countChar(entry, '/')){
                        // If the entry has associated texure/normal vertexes use all three to construct an ObjVertex
                        std::string* splitEntry = splitString(entry, '/');

                        int vIndex = atoi(splitEntry[0].c_str());
                        int vtIndex = atoi(splitEntry[1].c_str());
                        int vnIndex = atoi(splitEntry[2].c_str());


                        faceEls[i] = ObjVertex(vList[vIndex - 1], vtList[vtIndex - 1], vnList[vnIndex - 1]);

                        // Free used memory
                        delete[] splitEntry;
                    }
                    else{
                        // If the entry has just a standard vertex construct an ObjVertex using it and zeroes for all other elements
                        int vIndex = atoi(entry.c_str());

                        faceEls[i] = ObjVertex(vList[vIndex - 1], VertexTexture(0, 0), VertexNormal(0, 0, 0));
                    }
                }
                // Create a face and add it to the list of faces
                faces.push_back(Face(faceEls[0], faceEls[1], faceEls[2]));

            }

        // Free used memory
        delete[] splitStr;
    }
    // Return list of faces
    return faces;
 }


 std::vector<Face> ObjReader::readInFile(){
    return this->readInFile(std::map<std::string, Material>());
 }