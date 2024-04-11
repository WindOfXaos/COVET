#include "interface/interface.h"

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>
#include "core/app.h"
#include "scenes/objects.h"

#include <iostream>
void Interface::content(FrameBuffer* scene_buffer)
{
  // ImGui Docking Config
  // --------------------
  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode |
                                              ImGuiDockNodeFlags_AutoHideTabBar;
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking |
                                  ImGuiWindowFlags_NoDecoration |
                                  ImGuiWindowFlags_NoMove |
                                  ImGuiWindowFlags_MenuBar |
                                  ImGuiWindowFlags_NoBringToFrontOnFocus |
                                  ImGuiWindowFlags_NoNavFocus;

  ImGuiViewport* viewport = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

  if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      window_flags |= ImGuiWindowFlags_NoBackground;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1.0f, 0.0f));
  ImGui::Begin("Root", nullptr, window_flags);
  ImGui::PopStyleVar();
  ImGui::PopStyleVar(2);
  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
      ImGuiID dockspace_id = ImGui::GetID("Main Window");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

      static auto first_time = true;
      if (first_time)
      {
          first_time = false;
          // Clear out existing layout
          ImGui::DockBuilderRemoveNode(dockspace_id);
          // Add empty node
          ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
          // Main node should cover entire window
          ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetWindowSize());
          // get id of main dock space area
          ImGuiID dockspace_main_id = dockspace_id;
          // Create a dock node for the right docked window
          ImGuiID right = ImGui::DockBuilderSplitNode(dockspace_main_id, ImGuiDir_Right, 0.25f, nullptr, &dockspace_main_id);

          ImGui::DockBuilderDockWindow("Help", right);
          ImGui::DockBuilderDockWindow("Viewer", dockspace_main_id);
          ImGui::DockBuilderDockWindow("Settings", right);
          ImGui::DockBuilderFinish(dockspace_id);
      }
  }
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Create")) {}
      if (ImGui::MenuItem("Open", "Ctrl+O")) {}
      if (ImGui::MenuItem("Save", "Ctrl+S")) {}
      if (ImGui::MenuItem("Save as..")) {}
      if (ImGui::MenuItem("Exit")) {
        App& app = App::Get();
        app.Close();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
  // renderer viewport
  // -----------------
  ImGui::Begin("Viewer");
  {
      // Fill all the available width
      ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);
      if (ImGui::Button("Play", sz)){
        App::Get().GetWindowManager().ToggleMouse();
      }
      ImGui::BeginChild("Scene Window");
      float width = ImGui::GetContentRegionAvail().x;
      float height = ImGui::GetContentRegionAvail().y;
      WindowManager& wm = App::Get().GetWindowManager();
      wm.width = width;
      wm.height = height;
      ImGui::Image(
          (ImTextureID)(size_t)scene_buffer->getFrameTexture(),
          ImGui::GetContentRegionAvail(),
          ImVec2(0, 1),
          ImVec2(1, 0)
      );
      ImGui::EndChild();
  }
  ImGui::End();

  // UI content
  // ----------
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Sky Color", (float*)&skyColor);
  ImGui::Separator();
  if (ImGui::TreeNodeEx("Lighting Configuration", ImGuiTreeNodeFlags_DefaultOpen))
  {
      ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
      if (ImGui::BeginTabBar("Lighting Configuration", tab_bar_flags))
      {
          ImGuiColorEditFlags flags = ImGuiColorEditFlags_PickerHueWheel;
          if (ImGui::BeginTabItem("Sun (Directional Light)"))
          {
              ImGui::SetItemTooltip("Imitate sun light rays by specifying a direction vector.");
              ImGui::SliderFloat3("Direction", (float*)&sun.direction, 100.0f, -100.0f);
              ImGui::ColorEdit3("Ambient", (float*)&sun.ambient, flags);
              ImGui::SetItemTooltip("Illuminate objects evenly.");
              ImGui::ColorEdit3("Diffuse", (float*)&sun.diffuse, flags);
              ImGui::SetItemTooltip("Light reflected off objects.");
              ImGui::ColorEdit3("Specular", (float*)&sun.specular, flags);
              ImGui::SetItemTooltip("Light based of view direction.");
              ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Redstone Lamp (Point Light)"))
          {
              ImGui::SetItemTooltip("Illuminates in all directions and fades out over distance.");
              ImGui::ColorEdit3("Ambient", (float*)&redstoneLights.ambient, flags);
              ImGui::SetItemTooltip("Illuminate objects evenly.");
              ImGui::ColorEdit3("Diffuse", (float*)&redstoneLights.diffuse, flags);
              ImGui::SetItemTooltip("Light reflected off objects.");
              ImGui::ColorEdit3("Specular", (float*)&redstoneLights.specular, flags);
              ImGui::SetItemTooltip("Light based of view direction.");

              // plot attenuation formula in real-time
              ImGui::Separator();
              ImGui::Text("Distance Parameters");
              struct Funcs{
                  static float Atten(void*, int i) {return 1.0/(1.0 + redstoneLights.linear*i + redstoneLights.quadratic*i*i);}
              };
              float (*func)(void*, int) = Funcs::Atten;
              ImGui::PlotLines("", func, NULL, 20, 0, "Intensity VS. Distance", 0.0f, 1.2f, ImVec2(0, 80));
              ImGui::SliderFloat2("", (float*) &redstoneLights.linear, 0.0f, 4.0f);
              ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Flash Light (Spot Light)"))
          {
              ImGui::SetItemTooltip("Illuminates within a certain radius of the spotlight's direction.");
              ImGui::SliderFloat2("Inner/Outer Cutoff Angles", (float*)&flashLight.cutOffInner, 0.0f, 90.0f);
              ImGui::ColorEdit3("Ambient", (float*)&flashLight.ambient, flags);
              ImGui::SetItemTooltip("Illuminate objects evenly.");
              ImGui::ColorEdit3("Diffuse", (float*)&flashLight.diffuse, flags);
              ImGui::SetItemTooltip("Light reflected off objects.");
              ImGui::ColorEdit3("Specular", (float*)&flashLight.specular, flags);
              ImGui::SetItemTooltip("Light based of view direction.");

              // plot attenuation formula in real-time
              ImGui::Separator();
              ImGui::Text("Distance Parameters");
              struct Funcs{
                  static float Atten(void*, int i) {return 1.0/(1.0 + flashLight.linear*i + flashLight.quadratic*i*i);}
              };
              float (*func)(void*, int) = Funcs::Atten;
              ImGui::PlotLines("", func, NULL, 20, 0, "Intensity VS. Distance", 0.0f, 1.2f, ImVec2(0, 80));
              ImGui::SliderFloat2("", (float*) &flashLight.linear, 0.0f, 4.0f);
              ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
      }
      ImGui::TreePop();
  }
  if (ImGui::TreeNodeEx("Materials Configuration", ImGuiTreeNodeFlags_DefaultOpen))
  {
      ImGui::SliderFloat("Shininess", &mat.shininess, 1.0f, 256.0f);
      ImGui::SliderFloat("Reflectivity", &mat.reflectivity, 0.0f, 1.0f);
      ImGui::TreePop();
  }
  ImGui::End();

  // Help
  // ----
  ImGui::Begin("Help");
  ImGui::SeparatorText("CONTROLS:");
  ImGui::BulletText("Hit \"Play\" button above the viewer window to start playtesting.");
  ImGui::BulletText("WASD to move.");
  ImGui::BulletText("Scroll Wheel to zoom in/out.");
  ImGui::BulletText("ESC to pause playtesting.");

  ImGui::SeparatorText("SETTINGS:");
  ImGui::BulletText("\"Settings\" tab contains scene setup parameters.");
  ImGui::BulletText("Sky Color");
  ImGui::BulletText("Different lighting objects utilizing different light sources:\n"
                    "- Directional Light.\n- Point Light.\n- Spot Light\n"
                    "Each with its respective properties.");

  ImGui::SeparatorText("INTERFACE:");
  ImGui::ShowUserGuide();
  ImGui::End();
  ImGui::End();
}

void Interface::init(const WindowManager& wm){
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        DarkTheme();
        style.WindowRounding = 5.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(wm.window_handler, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Interface::End(){
    ImGuiIO& io = ImGui::GetIO();
    // App& app = App::Get();
		// io.DisplaySize = ImVec2((float)app.GetWindowManager().width, (float)app.GetWindowManager().height);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void Interface::Begin(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void Interface::DarkTheme()
{
	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

	// Headers
	colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	
	// Buttons
	colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Frame BG
	colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Tabs
	colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
	colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

	// Title
	colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
}

Interface::~Interface(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
