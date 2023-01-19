#include "Application.hpp"

struct Shader {
    GLuint id;
    string source;

    Shader(string *source, GLenum kind);
    ~Shader();
};