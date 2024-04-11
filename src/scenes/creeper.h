#pragma once

#include "core/scene.h"
#include "renderer/shader.h"
#include "renderer/model.h"
#include "renderer/loader.h"
#include "renderer/camera.h"

class CreeperScene : public Scene
{
  public:
    CreeperScene() = default;
    ~CreeperScene()
    {
      delete redstone_shader;
      delete creeper_shader;
      delete ground_shader;
      delete redstone;
      delete creeper;
      delete ground;
      delete fps_camera;
    }

    virtual void setup();
    virtual void update(float aspect_ratio);
    Camera& GetCamera() { return *fps_camera; }

  private:
    //  shaders
    Shader *redstone_shader = nullptr;
    Shader *creeper_shader = nullptr;
    Shader *ground_shader = nullptr;
    // models
    Model *redstone = nullptr;
    Model *creeper = nullptr;
    Model *ground = nullptr ;
    // camera
    Camera *fps_camera = nullptr;
};
