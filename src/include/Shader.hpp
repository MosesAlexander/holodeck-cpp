#ifndef SHADER_HEADERFILE_H
#define SHADER_HEADERFILE_H

//#include "Application.hpp"
#include <string>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Exception.hpp"

using namespace std;

struct Shader {
    GLuint id;

    Shader(const char *source, GLenum kind);
    Shader(Shader &&);
    Shader& operator=(Shader &&);
    ~Shader();
};

#endif