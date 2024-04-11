#pragma once

#include "core/window_manager.h"
#include "renderer/frame_buffer.h"

class Interface

{
    private:

    public:
        ~Interface();

        void init(const WindowManager& wm);
        void Begin();
        void content(FrameBuffer* sceneBuffer);
        void End();
        void DarkTheme();
};
