#ifndef PROGRAM_HEADERFILE_H
#define PROGRAM_HEADERFILE_H

#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "Shader.hpp"

struct Shader;

using namespace std;

struct Program {
    GLuint id;
    vector<GLuint> shader_ids;

    Program();
    ~Program();
    void add_shader(Shader *shader);
    int link_shaders();
};

#endif