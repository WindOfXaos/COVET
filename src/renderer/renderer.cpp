#include "renderer/shader.h"

#include <glad/glad.h>
#include <iostream>

void Renderer::init(const WindowManager& wm)
{
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    scene.setup();

    scene_buffer = new FrameBuffer(wm.width, wm.height);
}

void Renderer::update(const WindowManager& wm) {
    // bind framebuffer
    scene_buffer->Bind();

    scene.update((float)wm.width / wm.height);

    scene_buffer->Unbind();
}
