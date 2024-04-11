#include "renderer/loader.h"

#include <glad/glad.h>
#include "renderer/texture.h"

unsigned int Loader::createVAO()
{
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::storeDataInAttributeList(unsigned int attribNum, unsigned int coordSize, float *data, unsigned int size)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attribNum, coordSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attribNum);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
    glBindVertexArray(0);
}

Model Loader::loadToVAO(std::vector <float> positions, std::vector <float> normals, std::vector <float> texCoords)
{
    unsigned int vaoID = createVAO();
    storeDataInAttributeList(0, 3, positions.data(), positions.size() * sizeof(positions));
    storeDataInAttributeList(1, 3, normals.data(), normals.size() * sizeof(normals));
    storeDataInAttributeList(2, 2, texCoords.data(),  texCoords.size() * sizeof(texCoords));
    unbindVAO();
    return Model(vaoID, positions.size() / 3);
}

unsigned int Loader::loadTexture(int enumType, const char *file, int rgbType, bool flip)
{
    Texture texture;    
    texture.bind(enumType);
    texture.generateTexture(file, rgbType, flip);
    unsigned int textureID = texture.getTextureID();
    textures.push_back(textureID);
    return textureID;
}

void Loader::cleanUp()
{
    // clean VAOS
    for (auto vao : vaos)
    {
        glDeleteVertexArrays(1, &vao);
    }
    // clean VBOS
    for (auto vbo : vbos)
    {
        glDeleteBuffers(1, &vbo);
    }
    // clean textures
    for (auto texture : textures)
    {
        glDeleteTextures(1, &texture);
    }
}
