#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "camera.h"



const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates and color information
GLfloat vertices[] =
{ //    COORDINATES     /        COLORS        /    TexCoords
   -0.5f, 0.0f,  0.5f,    0.83f, 0.70f, 0.44f,     0.0f, 0.0f, 
   -0.5f, 0.0f, -0.5f,    0.83f, 0.70f, 0.44f,     5.0f, 1.0f, 
    0.5f, 0.0f, -0.5f,    0.83f, 0.70f, 0.44f,     0.0f, 1.0f, 
    0.5f, 0.0f,  0.5f,    0.83f, 0.70f, 0.44f,     5.0f, 0.0f,
    0.0f, 0.8f,  0.0f,    0.92f, 0.86f, 0.76f,     2.5f, 5.0f
};

// Order of vertices that compose each triangle (Indices)
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

GLfloat lightVertices[] = 
{
    //     COORDINATES     //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f,
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
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
    GLFWwindow* window = glfwCreateWindow(width, height, "MyGame", NULL, NULL);
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
    glViewport(0, 0, width, height);
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



    // Create shader for light source
    Shader lightShader("resources/shaders/light.vert", "resources/shaders/light.frag");

    // Generate and bind a Vertex Array Object for the light source
    VAO lightVAO;
    lightVAO.Bind();

    // Generate and bind a Vertex Buffer Object for the light source, and send the vertex data to the GPU
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    // Link the VBO to the VAO with the layout
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    // Unbind all to prevent accidentally modifying them
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();


    // Create transformations for the light source and the pyramid
    glm::vec3 lightPos(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    // Pyramid transformations
    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    // Send the transformations to the respective shaders
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));





    // Create texture
    Texture brick("resources/textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    // Enable depth testing for correct 3D rendering
    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


    // Main loop, where everything from input, logic changes and rendering happens
    while(!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);


        // Activate the shader before setting uniforms/drawing objects
        shaderProgram.Activate();
        camera.Matrix(shaderProgram, "camMatrix");
        // Bind the texture
        brick.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/sizeof(int), GL_UNSIGNED_INT, 0);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    brick.Delete();
    shaderProgram.Delete();
    // Loop ended, quit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 