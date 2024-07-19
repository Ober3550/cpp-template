# CPP App Template

### (SDL2, ImGui, CMake, vcpkg)

[Template from this blog](https://blog.kortlepel.com/c++/tutorials/2023/03/16/sdl2-imgui-cmake-vcpkg.html)

[**Dear ImGui**](https://github.com/ocornut/imgui) is a bloat-free graphical user interface library for C++. It outputs optimized vertex buffers that you can render anytime in your 3D-pipeline-enabled application. It is fast, portable, renderer agnostic, and self-contained (no external dependencies).

[**GLFW**](https://www.glfw.org/) (Graphics Library Framework) is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events.

[**OpenGL**](https://www.opengl.org/) (Open Graphics Library) is a cross-language, cross-platform application programming interface (API) for rendering 2D and 3D vector graphics. The API is typically used to interact with a graphics processing unit (GPU), to achieve hardware-accelerated rendering.

## How to use

Run the following to do the library installations according to cmake
`cmake -S . -B build`

If you get errors check that your c++ compiler and associated dev tooling (gcc stdc++ linking) are correct
One failure mode was clang pointing at gcc stdc++ 12 while only stdc++ 10 was installed

Then navigate to build and run
`make`

## Credits

-   Dear ImGui - https://github.com/ocornut/imgui
-   GLFW - https://www.glfw.org/
-   OpenGL - https://www.opengl.org/
