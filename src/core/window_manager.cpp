#include "core/window_manager.h"

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>
#include "core/app.h"

WindowManager::~WindowManager()
{
    glfwDestroyWindow(window_handler);
    glfwTerminate();
}

void WindowManager::init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window_handler = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window_handler == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window_handler);

    glfwSetWindowUserPointer(window_handler, this);

    // app icon
    SetIcon("icon.png");

    // Set GLFW callbacks
    glfwSetFramebufferSizeCallback(window_handler, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        App::Get().GetRenderer().scene_buffer->RescaleFrameBuffer(width, height);
    });

    glfwSetWindowSizeCallback(window_handler, [](GLFWwindow* window, int width, int height)
    {
        WindowManager& data = *(WindowManager *)glfwGetWindowUserPointer(window);

        // ternary operator to handle window minimize (wdith, height = 0) crashes
        data.width = width ? width : 1;
        data.height = height ? height : 1;

        // WindowResizeEvent event(width, height);
        // data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(window_handler, [](GLFWwindow* window)
    {
        WindowManager& data = *(WindowManager *)glfwGetWindowUserPointer(window);
        App::Get().Close();

        // WindowCloseEvent event;
        // data.EventCallback(event);
    });

    glfwSetKeyCallback(window_handler, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowManager& data = *(WindowManager *)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                if (key == GLFW_KEY_ESCAPE)
                  data.play = false;
                //KeyPressedEvent event(key, 0);
                //data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                //KeyReleasedEvent event(key);
                //data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                //KeyPressedEvent event(key, true);
                //data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetMouseButtonCallback(window_handler, [](GLFWwindow* window, int button, int action, int mods)
    {
        WindowManager& data = *(WindowManager *)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                //MouseButtonPressedEvent event(button);
                //data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                //MouseButtonReleasedEvent event(button);
                //data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(window_handler, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        WindowManager& data = *(WindowManager *)glfwGetWindowUserPointer(window);

        if (!data.play)
          return;

        App::Get().GetScene().GetCamera().ProcessMouseScroll(yOffset);
        //MouseScrolledEvent event((float)xOffset, (float)yOffset);
        //data.EventCallback(event);
    });

    glfwSetCursorPosCallback(window_handler, [](GLFWwindow* window, double xPos, double yPos)
    {
        WindowManager& data = *(WindowManager *)glfwGetWindowUserPointer(window);
        if (!data.play)
          return;

        if (data.first_mouse)
        {
            data.last_x = xPos;
            data.last_y = yPos;
            data.first_mouse = false;
        }

        float xoffset = xPos - data.last_x;
        float yoffset = data.last_y - yPos; // reversed since y-coordinates go from bottom to top

        data.last_x = xPos;
        data.last_y = yPos;

        App::Get().GetScene().GetCamera().ProcessMouseMovement(xoffset, yoffset);
        //MouseMovedEvent event((float)xPos, (float)yPos);
        //data.EventCallback(event);
    });


}

void WindowManager::update()
{
  float current_frame = glfwGetTime();
  dt = current_frame - last_frame;
  last_frame = current_frame;

  // tell GLFW to capture our mouse
  if (play)
  {
    processInput(window_handler);
    glfwSetInputMode(window_handler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
  else
  {
    first_mouse = true;
    glfwSetInputMode(window_handler, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }

  glfwSwapBuffers(window_handler);
  glfwPollEvents();
}

void WindowManager::processInput(GLFWwindow *window)
{
    Camera& camera = App::Get().GetScene().GetCamera();

    // movement usig WASD keys
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, dt);
}

void WindowManager::SetIcon(const char* icon)
{
  GLFWimage images[1];
  images[0].pixels = stbi_load(icon, &images[0].width, &images[0].height, 0, 4);
  glfwSetWindowIcon(window_handler, 1, images);
  stbi_image_free(images[0].pixels);
}
