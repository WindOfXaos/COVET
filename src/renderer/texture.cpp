#include "renderer/texture.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture()
{
    glGenTextures(1, &ID);
}

void Texture::bind(int enumType)
{
    this->enumType = enumType;
    glBindTexture(enumType, ID);
}

void Texture::generateTexture(const char *file, int rgbType, bool flip)
{
    int width, height, nrChannels;
    if(flip)
        stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
        
    if (data)
    {
        glTexImage2D(enumType, 0, rgbType, width, height, 0, rgbType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(enumType);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        glfwTerminate();
        exit(1);
    }
    stbi_image_free(data);
}
