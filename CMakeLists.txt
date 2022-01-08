cmake_minimum_required(VERSION 3.1)

project(Raymarcher VERSION 1.0)

add_executable(Raymarcher main.cpp raymarcher.cpp shader.cpp)
target_link_libraries(Raymarcher PUBLIC m GL GLEW SDL2)

