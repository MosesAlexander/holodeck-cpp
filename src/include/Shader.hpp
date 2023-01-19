#include "Application.hpp"

struct Shader {
    GLuint id;
    string source;

    Shader(const char *source, GLenum kind);
    ~Shader();
};