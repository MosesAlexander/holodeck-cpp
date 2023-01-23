#ifndef TEXTMANAGER_HEADERFILE_H
#define TEXTMANAGER_HEADERFILE_H

#include <ft2build.h>
#include "Program.hpp"
#include "Uniform.hpp"

#include FT_FREETYPE_H

struct Character {
    uint32_t texture_id;
    glm::vec2 size;
    glm::vec2 bearing;
    uint32_t advance;
};

struct TextManager {
    Program *program;
    UniformDescriptor text_uniform;
    UniformDescriptor text_projection_uniform;
    glm::mat4 text_projection;
    std::map<char, Character> characters;
    gl::types::GLuint text_vao;
    gl::types::GLuint text_vbo;

    TextManager(Program *program);
    TextManager(TextManager&&);
    TextManager& operator=(TextManager&&);

    void init();
    void use_text_program();
    void render_text(std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif