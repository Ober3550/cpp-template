cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Set the compiler to clang
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)

# Pull the latest version of vcpkg and run it
include(vcpkg.cmake)

project(
    "cpp-template"
    VERSION 0.1.0
    LANGUAGES CXX
)

# add all headers (.h, .hpp) to this
set(PRJ_HEADERS 
    src
)

# add all source files (.cpp) to this, except the one with main()
set(PRJ_SOURCES 
    src/rendering/app.cpp
    src/rendering/mesh.cpp
    src/rendering/camera.cpp
    src/rendering/object.cpp
)

# set the source file containing main()
set(PRJ_MAIN 
    src/main.cpp
)

# add dependency find_package calls and similar here
find_package(fmt CONFIG REQUIRED)
find_package(imgui REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)

# Optionally set the compiler to emcc
# set(CMAKE_CXX_COMPILER emcc)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_WEBGL2=1 -s USE_GLFW=3 -s FULL_ES3=1 -s WASM=1")

add_executable(${PROJECT_NAME} ${PRJ_HEADERS} ${PRJ_SOURCES} ${PRJ_MAIN})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${PRJ_LIBRARIES})

IF (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        fmt::fmt
        imgui::imgui
        glm::glm
        unofficial::gl3w::gl3w
        opengl32.lib
    )
ELSE()
	target_link_libraries(${PROJECT_NAME} PRIVATE 
        fmt::fmt
        imgui::imgui
        glm::glm
        unofficial::gl3w::gl3w
        OpenGL::GL
    )
ENDIF()

# Copy shaders to build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory              
        ${CMAKE_SOURCE_DIR}/src/shaders shaders
    COMMENT "Copying shaders" VERBATIM
)
