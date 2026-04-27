#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

in vec3 normal;
in vec3 crntPos;

uniform sampler2D tex0;

uniform vec4 lightColor; // Uniform variable for light color
uniform vec3 lightPos; // Uniform variable for light position
uniform vec3 camPos; // Uniform variable for camera position

void main()
{
    float ambientStrength = 0.20f; // Ambient light strength

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - crntPos);

    float diffuse = max(dot(norm, lightDir), 0.0f); // Diffuse lighting calculation

    float specularStrength = 0.5f; // Specular light strength
    vec3 viewDir = normalize(camPos - crntPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 8); // Specular lighting calculation
    float specular = specularStrength * specAmount;

    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambientStrength + specular); // Combine texture color with lighting
}