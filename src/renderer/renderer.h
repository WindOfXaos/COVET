#pragma once

#include "core/scene.h"
#include "core/window_manager.h"
#include "renderer/frame_buffer.h"

class Renderer
{
private:
    Scene &scene;

public:
    Renderer(Scene &s): scene(s) {};

    FrameBuffer *scene_buffer;
    void init(const WindowManager& wm);
    void update(const WindowManager& wm);
};
