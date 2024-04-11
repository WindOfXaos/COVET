#pragma once

#include <vector>
#include "model.h"

class Loader
{
private:
    std::vector <unsigned int> vaos;
    std::vector <unsigned int> vbos;
    std::vector <unsigned int> textures;

    unsigned int createVAO();
    void storeDataInAttributeList(unsigned int attribNum, unsigned int coordSize, float *data, unsigned int size);
    void unbindVAO();

public:
    Model loadToVAO(std::vector <float> positions, std::vector <float> normals, std::vector <float> texCoords);
    unsigned int loadTexture(int enumType, const char *file, int rgbType, bool flip = false);
    void cleanUp();
};
