#include<iostream>

#include"../world/vectors.hpp"

/**
 * @brief Output an Array of Pixels to a P6 PPM image
 * 
 * @param file The file to print the image data to
 * @param outputFrom The array of Pixel objects to use as the image
 * @param imgWidth The width of the image to output in pixels
 * @param imgHeight The height of the image to output in pixels
 * @return The fiel stream being printed to after the image has been written
 */
std::ofstream& PPMOut(std::ofstream& file, Color** outputFrom, int imgLength, int imgWidth);