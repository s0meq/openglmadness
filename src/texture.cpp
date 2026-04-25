#include "texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;

    // Load the image
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true); // Flip the image vertically during loading
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generate texture and bind it
    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Set the texture wrapping parameters
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set the texture filtering parameters
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Load the texture to OpenGL
    glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    // Free the image memory and unbind the texture
    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    // Get the location of the uniform
    GLuint uniID = glGetUniformLocation(shader.ID, uniform);
    // Activate the shader
    shader.Activate();
    // Set the value of the uniform to the texture unit
    glUniform1i(uniID, unit);
}

void Texture::Bind()
{
    glBindTexture(type, ID);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}