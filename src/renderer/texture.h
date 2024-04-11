#pragma once

class Texture
{
private:
  unsigned int ID;
  int enumType;

public:
  Texture();
  void bind(int enumType);
  void generateTexture(const char* file, int rgbType, bool flip);

  unsigned int getTextureID() {return ID;}
  unsigned int getTextureEnumType() {return enumType;}

};
