#include "shader.hpp"

#include <cwchar>
#include <fstream>
#include <iostream>

shader::shader() {}

shader::shader(std::string v, std::string f)
    : vertex_shader_file{v}, fragment_shader_file{f} {
  try {
    shader::read_files();
  } catch (std::string &e) {
    std::cerr << "Caught shader exception: " << e << std::endl;
  }
}

shader::~shader() {}

void shader::init() {
  _vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  _fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  _program = glCreateProgram();
  try {
    shader::source_and_compile();
    shader::attach_and_link();
  } catch (std::string &e) {
    std::cerr << "Caught shader exception: " << e << std::endl;
  }
  glDeleteShader(_vertex_shader);
  glDeleteShader(_fragment_shader);
}

void shader::cleanup()
{
  glDeleteProgram(_program);
}

void shader::read_files() {
  std::ifstream file(vertex_shader_file);
  std::string line;
  if (file.good()) {
    while (getline(file, line)) {
      vertex_shader_source += line + "\n";
    }
  } else {
    throw "Could not open vertex shader source at " + vertex_shader_file;
  }
  file.close();

  // same for fragment shader
  file.open(fragment_shader_file);
  if (file.good()) {
    while (getline(file, line)) {
      fragment_shader_source += line + "\n";
    }
  } else {
    throw "Could not open fragment shader source at " + fragment_shader_file;
  }
  file.close();
}

void shader::source_and_compile() {
  // source and compile shaders
  const char *v = vertex_shader_source.c_str();
  const char *f = fragment_shader_source.c_str();

  glShaderSource(_vertex_shader, 1, &v, NULL);
  glCompileShader(_vertex_shader);
  GLint success;
  glGetShaderiv(_vertex_shader, GL_COMPILE_STATUS, &success);

  char error_string[512];
  if (!success) {
    glGetShaderInfoLog(_vertex_shader, 512, NULL, error_string);
    throw std::string(error_string);
  }

  glShaderSource(_fragment_shader, 1, &f, NULL);
  glCompileShader(_fragment_shader);
  glGetShaderiv(_fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(_fragment_shader, 512, NULL, error_string);
    throw std::string(error_string);
  }
}
void shader::attach_and_link() {
  GLint success;
  GLchar error_string[512];
  glAttachShader(_program, _vertex_shader);
  glAttachShader(_program, _fragment_shader);
  glLinkProgram(_program);
  glGetProgramiv(_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(_program, 512, NULL, error_string);
    throw std::string(error_string);
  }
}

void shader::use() { glUseProgram(_program); }
