#include "Game2048.h"

int main(int argc, char **argv)
{
    // Initialize glfw 
    glfwInit();

    // Create window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "Game2048", NULL, NULL);
    // Check whether window was created successfully
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make window current context
    glfwMakeContextCurrent(window);

    // Set viewport
    glViewport(0, 0, 800, 600);
    
    // Specify the color for the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    
    // Clean the background color and assign a new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Destroy window object
    glfwDestroyWindow(window);
    
    // Terminate GLFW
    glfwTerminate();
    return 0;
}