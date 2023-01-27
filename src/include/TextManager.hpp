#ifndef TEXTMANAGER_HEADERFILE_H
#define TEXTMANAGER_HEADERFILE_H

#include <ft2build.h>

#include FT_FREETYPE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "Program.hpp"
#include "Uniform.hpp"

using namespace std;

struct Character {
    uint32_t texture_id;
    glm::vec2 size;
    glm::vec2 bearing;
    int64_t advance;
};

struct TextManager {
    Program *program;
    UniformDescriptor text_uniform;
    UniformDescriptor text_projection_uniform;
    glm::mat4 text_projection;
    std::map<char, Character> characters;
    GLuint text_vao;
    GLuint text_vbo;
    FT_Library ft;
    FT_Face face;

    TextManager(Program *program);
    TextManager(TextManager&&);
    TextManager();
    TextManager& operator=(TextManager&&);

    int init();
    void use_text_program();
    void render_text(std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif