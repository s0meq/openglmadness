#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture coordinates
layout (location = 2) in vec2 aTex;

layout (location = 3) in vec3 aNormal;

// Outputs the color to the fragment shader
out vec3 color;

// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

out vec3 normal;
out vec3 crntPos;

// Imports the camera matrix from the application, which is the combination of the projection and view matrices
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    crntPos = vec3(model * vec4(aPos, 1.0));

    // Calculates the position of each vertex, by multiplying the position by the scale, 
    // and then multiplying it by the model, view and projection matrices
    gl_Position = camMatrix * vec4(crntPos, 1.0);
    // Outputs the colors of Vertex data to "color" variable, which will be used in the fragment shader
    color = aColor;
    // Outputs the texture coordinates
    texCoord = aTex;
    normal = aNormal;
}