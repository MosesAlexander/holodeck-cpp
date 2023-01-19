#include "Shader.hpp"

struct Program {
    GLuint id;
    vector<GLuint> shader_ids;

    Program();
    ~Program();
    void add_shader(Shader *shader);
    int link_shaders();
};

