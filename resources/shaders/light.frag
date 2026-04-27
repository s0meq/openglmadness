#version 330 core

out vec4 FragColor;

uniform vec4 lightColor; // Uniform variable for light color

void main()
{
    FragColor = lightColor; // Set the fragment color to the light color
}