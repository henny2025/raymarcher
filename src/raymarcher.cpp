#include "raymarcher.hpp"
#include "shader.hpp"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

#define ASSETS_DIR "/usr/local/share/raymarcher"

raymarcher::raymarcher(int width, int height)
    : window_height(height), window_width(width) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Raymarcher Constructor: Failed to initialize SDL"
              << std::endl;
  }

  m_window =
      SDL_CreateWindow("OpenGL Fractal Renderer", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, window_width, window_height,
                       SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (m_window == NULL) {
    std::cerr << "Raymarcher Constructor: failed to create SDL Window: "
              << SDL_GetError() << std::endl;
  }

  m_context = SDL_GL_CreateContext(m_window);
  if (m_context == NULL) {
    std::cerr << "Raymarcher Constructor: failed to create SDL Context: "
              << SDL_GetError() << std::endl;
  }

  SDL_GL_MakeCurrent(m_window, m_context);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  GLenum glew_ok = glewInit();
  if (glew_ok != GLEW_OK) {
    std::cerr << "Raymarcher Constructor: failed to initialize GLEW"
              << glewGetErrorString(glew_ok) << std::endl;
  }

  //TODO: figure out how to do smart directory finding
  std::string vertex_shader_path(ASSETS_DIR, "/vertex.glsl");
  std::string fragment_shader_path(ASSETS_DIR, "/fragment.glsl");

  shader(vertex_shader_path, fragment_shader_path);
}

raymarcher::raymarcher() : raymarcher::raymarcher(600, 800) {}

raymarcher::~raymarcher() {
  SDL_DestroyWindow(m_window);
  SDL_Quit();
  glDeleteVertexArrays(1, &_vao);
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ebo);
}

void raymarcher::main_loop() {

  SDL_Event ev;

  while (!should_close) {
    // TODO: just render 10fps to prevent bottlenecking for now
    render_frame();
    SDL_PollEvent(&ev);
    process_event(&ev);
    SDL_Delay(100);
  }
}

void raymarcher::setup_vao() {
  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);
  glGenBuffers(1, &_ebo);

  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(corners), corners, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(corner_indices), corner_indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void raymarcher::render_frame() {
  _shader.use();
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
  SDL_GL_SwapWindow(m_window);
}

void raymarcher::process_event(SDL_Event *ev) {
  if (ev->window.type == SDL_WINDOWEVENT_CLOSE) {
    should_close = true;
  }
}
