#include "core/app.h"

App* App::instance = nullptr;

App::App(const char *title, unsigned int width, unsigned int height, bool offscreen): wm(title, width, height, offscreen), renderer(scene)
{
  wm.init();
  renderer.init(wm);
  ui.init(wm);
}

void App::Run()
{
  while (running)
  {
    ui.Begin();
    renderer.update(wm);
    ui.content(renderer.scene_buffer);
    ui.End();
    wm.update();
  }
}
