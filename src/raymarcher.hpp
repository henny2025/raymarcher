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
    float corners[8] = {
         1,  1,   // top right
         1, -1,   // bottom right
         -1, -1,   // bottom left
        -1,  1,   // top left 
    };
    unsigned int corner_indices[6] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    void setup_vao();
};

#endif
