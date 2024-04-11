#include "renderer/model.h"
#include <glad/glad.h>

void Model::draw() {
    glBindVertexArray(this->getVaoID());

    // textures binding (diffuse and specular)
    unsigned int *textureIDs = this->getTextureIDs();
    unsigned int IDs = this->getNumOfTextIDs();
    for(unsigned int i = 0; i < IDs; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
    }

    glDrawArrays(GL_TRIANGLES, 0, this->getVertexCount());
    glBindVertexArray(0);
}
