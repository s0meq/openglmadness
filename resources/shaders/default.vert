#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTex;

// Outputs the color to the fragment shader
out vec3 color;


out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
    // Calculates the position of each vertex, by multiplying the position by the scale, 
    // and then multiplying it by the model, view and projection matrices
    gl_Position = camMatrix * vec4(aPos, 1.0);
    // Outputs the colors of Vertex data to "color" variable, which will be used in the fragment shader
    color = aColor;
    // Outputs the texture coordinates
    texCoord = aTex;
}