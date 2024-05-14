#pragma once

#include "core/window_manager.h"
#include "renderer/renderer.h"
#include "interface/interface.h"
#include "scenes/creeper.h"

class App
{
private:
  App(const char *title, unsigned int width, unsigned int height);
  App(const App&) = delete;
  App& operator=(const App&) = delete;

public:
  static App& Create(const char *title, unsigned int width, unsigned int height)
  {
    static App instance(title, width, height);
    return instance;
  }

  static App& Get()
  {
    return Create("", 0, 0);
  }

  WindowManager& GetWindowManager() { return wm; }
  CreeperScene& GetScene() { return scene; }
  Renderer& GetRenderer() { return renderer; }
  void Run();
  void Close() { running = false; }

private:
  static App *instance;

  bool running = true;

  WindowManager wm;
  CreeperScene scene;
  Renderer renderer;
  Interface ui;
};
