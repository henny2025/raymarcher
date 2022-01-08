add_executable(raymarcher main.cpp raymarcher.cpp shader.cpp)
target_link_libraries(raymarcher PUBLIC m GL GLEW SDL2)
