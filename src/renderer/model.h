#pragma once

#include <vector>

class Model
{

private:
    unsigned int vaoID;
    unsigned int vertexCount;
    std::vector <unsigned int> textureIDs;
    unsigned int numOfTextIDs = 0;

public:
    Model(int vaoID, int vertexCount)
    {
        this->vaoID = vaoID;
        this->vertexCount = vertexCount;
    }

    void addTexture(unsigned int textureID)
    {
        textureIDs.push_back(textureID);
        numOfTextIDs ++;
    }

    unsigned int getVaoID()
    {
        return vaoID;
    }

    unsigned int *getTextureIDs()
    {
        return textureIDs.data();
    }

    unsigned int getNumOfTextIDs()
    {
        return numOfTextIDs;
    }

    unsigned int getVertexCount()
    {
        return vertexCount;
    }

    void draw();
};
