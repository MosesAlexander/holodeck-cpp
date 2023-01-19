#ifndef PROGRAM_HEADERFILE_H
#define PROGRAM_HEADERFILE_H

#include "Shader.hpp"

struct Program {
    GLuint id;
    vector<GLuint> shader_ids;

    Program();
    ~Program();
    void add_shader(Shader *shader);
    int link_shaders();
};

#endif