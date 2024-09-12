#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"gpuRender.hpp"
#include"vectors.hpp"
#include"shaders.hpp"



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
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);



    while (!glfwWindowShouldClose(window)) {
        // Clear the frame
        glClear(GL_COLOR_BUFFER_BIT);



    }

    // Cleanup window on close
    glfwTerminate();
    return true;
}


/// @brief Handle resizing of the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}


void render(unsigned int shaderProg, float* vertArray, float* cameraTransform){

}
