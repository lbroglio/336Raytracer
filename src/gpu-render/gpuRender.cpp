#include"../../include/glad/glad.h"
#include<GLFW/glfw3.h>


#include"gpuRender.hpp"
#include"../world/vectors.hpp"
#include"shaders.hpp"
#include"../file-io/modelReaders.hpp"

void render(unsigned int shaderProg, int numPoints, GLuint* bufferIndices, float* cameraTransform);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool renderWithGPU(std::vector<Face>* faces, Color worldColor, Vertex cameraPos, int cameraPitch, int cameraYaw){
    // Create array to hold vertices and color data
    float vertArray[faces->size() * 21];

    // Load array with data
    for(size_t i =0; i < faces->size(); i++){
        // Get face to load 
        Face currFace = faces->at(i);

        int startingIndex = i * 21;

        // Load vertices and colors

        // Load v1 
        vertArray[startingIndex] = currFace.v1.v.x;
        vertArray[startingIndex + 1] = currFace.v1.v.y;
        vertArray[startingIndex + 2] = currFace.v1.v.z;

        // Load color for v1
        vertArray[startingIndex + 3] = currFace.mat.ambientComponent.r;
        vertArray[startingIndex + 4] = currFace.mat.ambientComponent.b;
        vertArray[startingIndex + 5] = currFace.mat.ambientComponent.g;
        vertArray[startingIndex + 6] = 1.0f;

        // Load v2
        vertArray[startingIndex + 7] = currFace.v2.v.x;
        vertArray[startingIndex + 8] = currFace.v2.v.y;
        vertArray[startingIndex + 9] = currFace.v2.v.z;

        // Load color for v2
        vertArray[startingIndex + 10] = currFace.mat.ambientComponent.r;
        vertArray[startingIndex + 11] = currFace.mat.ambientComponent.b;
        vertArray[startingIndex + 12] = currFace.mat.ambientComponent.g;
        vertArray[startingIndex + 13] = 1.0f;

        // Load v3
        vertArray[startingIndex + 14] = currFace.v2.v.x;
        vertArray[startingIndex + 15] = currFace.v2.v.y;
        vertArray[startingIndex + 16] = currFace.v2.v.z;

        // Load color for v3
        vertArray[startingIndex + 17] = currFace.mat.ambientComponent.r;
        vertArray[startingIndex + 18] = currFace.mat.ambientComponent.b;
        vertArray[startingIndex + 19] = currFace.mat.ambientComponent.g;
        vertArray[startingIndex + 20] = 1.0f;
    }


    glfwInit();
    

    // Create a new window 
    GLFWwindow* window = glfwCreateWindow(800, 600, "336Raytrace Standard Rendering", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Initialize GLADD
    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }   

    // Set up view port and resizing  
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    // Set clear color
    glClearColor(worldColor.r, worldColor.g, worldColor.b, 1.0f);

    // Enable vsync
    glfwSwapInterval(1);

    // Load and compile shaders
    unsigned int vShader;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &V_SHADER_SOURCE, NULL);
    glCompileShader(vShader);

    // Check if shader compilation was sucessful
    int  success;
    char infoLog[512];
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "Error: Vertex shader compilation failed. Root Cause: " << infoLog << std::endl;
    }

    unsigned int fShader;
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &F_SHADER_SOURCE, NULL);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "Error: Fragment shader compilation failed. Root Cause: " << infoLog << std::endl;
    }

    // Create shader program
    unsigned int prog;
    prog = glCreateProgram();
    glAttachShader(prog, vShader);
    glAttachShader(prog, fShader);
    glLinkProgram(prog);

    // Delete the programs as they are no longer needed
    glDeleteShader(vShader);
    glDeleteShader(fShader); 

    // Create buffers
    GLuint bufferIndices[1];
    glGenBuffers(1, bufferIndices);

    // Load the buffer
    glBindBuffer(GL_ARRAY_BUFFER, bufferIndices[0]);
    GLsizeiptr bufferSize = sizeof(float) * faces->size() * 21;
    glBufferData(GL_ARRAY_BUFFER, bufferSize, vertArray, GL_STATIC_DRAW);


    while (!glfwWindowShouldClose(window)) {
        // Clear the frame
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the frame
        render(prog, faces->size() * 3, bufferIndices, 0);
    }

    // Cleanup buffers
    glDeleteBuffers(1, bufferIndices);

    // Cleanup window on close
    glfwTerminate();
    return true;
}


/// @brief Handle resizing of the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}


void render(unsigned int shaderProg, int numPoints, GLuint* bufferIndices, float* cameraTransform){

    // Use the program 
    glUseProgram(shaderProg); 

    // Find position attribute
    int positionLoc = glGetAttribLocation(shaderProg, "a_Position");
    if (positionLoc < 0) {
        std::cout << "Error: Failed to find a_Position attribute location" << std::endl;
        return;
    }

    // Find color attribute
    int colorLoc = glGetAttribLocation(shaderProg, "a_Position");
    if (colorLoc < 0) {
        std::cout << "Error: Failed to find a_Color attribute location" << std::endl;
        return;
    }

    // "enable" the attributes
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(colorLoc);


    // Setup stride and offet
    GLintptr vertexColorOffset = 3 * sizeof(float);
    int vertexStride = 4 * sizeof(float);

    // Buffer data into the position and color attributes
    glBindBuffer(GL_ARRAY_BUFFER, bufferIndices[0]);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, vertexStride, 0);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, vertexStride,  (GLvoid*) vertexColorOffset);

    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Draw the image
    glDrawArrays(GL_TRIANGLES, 0, numPoints);

    // Unbind the program and disable attributes
    glDisableVertexAttribArray(positionLoc);
    glDisableVertexAttribArray(colorLoc);
    glUseProgram(0);
}

int main(int argc, char* argv[]){
    // Setup program configurations
    Configurator config;

    // If a configuration file was given on the command line use it to set program configs
    if(argc > 3){
        ConfigReader cReader = ConfigReader(argv[3]);

        config =  cReader.readInFile();
    }

    // Read in the .mtl file specified by the second argument
    MtlReader mReader(argv[2]);
    std::map<std::string, Material> mats = mReader.readInFile();

    // Read in the .obj file specified by the first argument
    ObjReader oReader(argv[1]);
    std::vector<Face> faces = oReader.readInFile(mats);

    renderWithGPU(&faces, config.worldColor, config.cameraPos, 0, 0);
}
