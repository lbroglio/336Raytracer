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
 * @brief Split a string into an array of subs strings divided by the whitespace (' ' chars from the string)
 * Allocates memory for the the array
 * 
 * @param toSplit The string to split up by whitespace
 * 
 * @return An allocated array of sub strings
 * 
 */
std::string* splitString(std::string toSplit){
    // Find number of spaces in the string
    int numSpaces = countChar(toSplit, ' ');

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
        if(currChar == ' '){
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
        std::string* splitStr = splitString(line);

       
        

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

    }

    // Save the last read in material
    Material parsedMat(Ka, Kd, Ks, shininess);
    matMap.insert({mtlName, parsedMat});

    // Return the mapping of materials
    return matMap;
}