#pragma once

class Scene
{
  public:
    virtual void setup() = 0;
    virtual void update(float aspect_ratio) = 0;
};
