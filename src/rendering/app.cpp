#include "app.h"

App::App(AppSettings settings) {
  // Save settings into app class
  deltaTimeTarget = 1000.0 / (double)settings.frameRate;

  // Setup window
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize glfw\n");
  }

  // OpenGL 3.2 + GLSL 150
  const char *glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  const int WIN_WIDTH = 1280;
  const int WIN_HEIGHT = 720;

  // Create window with graphics context
  window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "CPP Template", NULL, NULL);
  if (window == NULL) {
    throw std::runtime_error("Failed to create OpenGL window\n");
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = std::addressof(ImGui::GetIO());
  io->ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
  //  Gamepad Controls
  io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
  io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport
                                                       // / Platform Windows
  // io->ConfigViewportsNoAutoMerge = true;
  // io->ConfigViewportsNoTaskBarIcon = true;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform
  // windows can look identical to regular ones.
  ImGuiStyle &style = ImGui::GetStyle();
  if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Opengl template based on this tutorial:
  // https://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
  if (gl3wInit()) {
    throw std::runtime_error("Failed to initialize OpenGL\n");
  }
}

void App::BeginFrame() {
  // Handle event loop
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  glfwPollEvents();

  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
}

void App::EndFrame() {
  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Update and Render additional Platform Windows
  // (Platform functions may change the current OpenGL context, so we
  // save/restore it to make it easier to paste this code elsewhere.
  //  For this specific demo app we could also call
  //  glfwMakeContextCurrent(window) directly)
  if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }

  glfwSwapBuffers(window);

  // Get the time between the last frame and current
  double now = (1000.0 * glfwGetTime());
  deltaTime = now - lastFrameTime;

  // If we finished the frame early sleep the difference
  int sleepTime = (int)(deltaTimeTarget - deltaTime);
  if (sleepTime > 0) {
    // WSL doesn't have a vsync signal
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
  }

  // Recalculate lastFrameTime after sleep
  now = (1000.0 * glfwGetTime());
  deltaTime = now - lastFrameTime;
  lastFrameTime = now;
}

void App::Exit() {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
}