#ifndef RAYMARCHER_HPP
#define RAYMARCHER_HPP

#include "shader.hpp"
#include <SDL2/SDL.h>

class raymarcher {
  public:
    raymarcher();
    raymarcher(int width, int height);
    ~raymarcher();

    void main_loop();
  private:
    SDL_Window *m_window;
    SDL_GLContext m_context;

    int window_height;
    int window_width;
    bool should_close{false};

    GLuint _vbo, _ebo, _vao;
    shader _shader;

    void process_event(SDL_Event *);
    void render_frame();

    // for vbo and ebo
    float corners[8] = {-1.0, 1.0,
      1.0, 1.0,
      1.0, -1.0,
      -1.0, -1.0};
    unsigned int corner_indices[4] = {1, 2, 3, 4};

    void setup_vao();
};

#endif
