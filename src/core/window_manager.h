#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// window class
// ------------
class WindowManager
{
public:
    GLFWwindow *window_handler = nullptr;
    const char *title;
    unsigned int width;
    unsigned int height;
    bool play = false;

    WindowManager(const char *t, int w, int h): title(t), width(w), height(h) {}
    ~WindowManager();
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    void init();
    void update();
    void SetIcon(const char *icon);
    void ToggleMouse() { play = !play; }
    void processInput(GLFWwindow *window);

private:
    // callback functions variables
    float last_x;
    float last_y;
    bool first_mouse = true;
    float dt = 0.0f;
    float last_frame = 0.0f;
};
