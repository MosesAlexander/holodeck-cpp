#ifndef SHADER_HEADERFILE_H
#define SHADER_HEADERFILE_H

#include "Application.hpp"

struct Shader {
    GLuint id;
    std::string source;

    Shader(const char *source, GLenum kind);
    ~Shader();
};

#endif