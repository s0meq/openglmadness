#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTex;

// Outputs the color to the fragment shader
out vec3 color;


out vec2 texCoord;


// Controls the scale of the vertices
uniform float scale;

void main()
{
    // Outputs the positions/coordinates of all vertices
    gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    // Outputs the colors of Vertex data to "color" variable, which will be used in the fragment shader
    color = aColor;
    // Outputs the texture coordinates
    texCoord = aTex;
}