#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
// Vertices coordinates and color information
GLfloat vertices[] =
{ //    COORDINATES     /     COLORS
   -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,  // Lower Left Corner
   -0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,     0.0f, 1.0f, // Upper Left corner
    0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,     1.0f, 1.0f,  // Upper Right corner
    0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,     1.0f, 0.0f  // Lower Right corner
};

// Order of vertices that compose each triangle (Indices)
GLuint indices[] =
{
    0, 2, 1, // Upper triangle
    0, 3, 2  // Lower triangle
};

int main () {
    glfwInit();
    std::cout << "GLFW initialized successfully" << std::endl;
    // Tell GLFW what version of OpenGL we use (3.3 in this case)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we use the CORE profile, so we only have the modern funcs
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window object, width x height (?), naming it "MyGame"
    GLFWwindow* window = glfwCreateWindow(800, 800, "MyGame", NULL, NULL);
    if (window == NULL)
    {
        // If window initialization failed, terminate and return -1
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "GLFW window created successfully" << std::endl;
    // Make the above created window current context
    glfwMakeContextCurrent(window);
    // Load GLAD so we can use gl functions
    gladLoadGL();
    // Specify the viewport size
    glViewport(0, 0, 800, 800);
    std::cout << "GLAD loaded successfully, OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    // Create shader program using the shader class
    Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");
    std::cout << "Shader program created with ID: " << shaderProgram.ID << std::endl;

    // Generate and bind a Vertex Array Object
    VAO VAO1;
    VAO1.Bind();

    // Generate and bind a Vertex Buffer Object, and send the vertex data to the GPU
    VBO VBO1(vertices, sizeof(vertices));

    // Generate and bind an Element Buffer Object, and send the index data to the GPU
    EBO EBO1(indices, sizeof(indices));

    // Link the VBO to the VAO with the layout
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Gets ID of uniform called "scale" from the shader program
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


    Texture texture("resources/textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);


    std::cout << "VAO, VBO and EBO created and linked successfully, starting rendering..." << std::endl;
    // Main loop, where everything from input, logic changes and rendering happens
    while(!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();
        // Assign a value for the uniform; NOTE: Must always be done after activating the Shader Program
        glUniform1f(uniID, 0.5f);
        texture.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    texture.Delete();
    shaderProgram.Delete();
    // Loop ended, quit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 