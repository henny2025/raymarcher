#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>

class shader {
  public:
    shader();
    shader(std::string, std::string);
    ~shader();
    inline GLuint get_program() {return _program;}
    void use();
    void init();
    void cleanup();
  private:
    GLuint _program, _vertex_shader, _fragment_shader;

    const std::string vertex_shader_file, fragment_shader_file;
    std::string vertex_shader_source, fragment_shader_source;
    bool error;
    std::string error_string;

    void read_files();
    void source_and_compile();
    void attach_and_link();
};

#endif
