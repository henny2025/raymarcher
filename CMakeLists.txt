cmake_minimum_required(VERSION 3.1)

project(raymarcher VERSION 1.0)
add_subdirectory(src)
add_subdirectory(assets)


install(TARGETS raymarcher
  CONFIGURATIONS Debug Release
  DESTINATION bin)
install(DIRECTORY assets/ DESTINATION share/raymarcher FILES_MATCHING PATTERN "*.glsl")


