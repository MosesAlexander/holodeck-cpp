#include "TextManager.hpp"

TextManager::TextManager(Program *program) {
    UniformDescriptor text_uniform(program->id, "textColor");
    UniformDescriptor text_projection_uniform(program->id, "projection"); 
    this->text_uniform = text_uniform;
    this->text_projection_uniform = text_projection_uniform;

    this->text_projection = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, 0.1f, 100.0f);

    glGenVertexArrays(1, &text_vao);
    glGenBuffers(1, &text_vbo);
    glBindVertexArray(text_vao);
    glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(float) * 6 * 4,
        NULL,
        GL_DYNAMIC_DRAW
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 4,
        (void*)0
    );

    if (init()) {
        std::cerr<<"There was a problem initializing TextManager"<<std::endl;
        throw application_exception("There was a problem initializing TextManager");
    }
}

int TextManager::init() {
    if (FT_Init_FreeType(&ft)) {
        std::cerr<<"ERROR::FREETYPE: Could not init FreeType library"<<std::endl;
        return -1;
    }

    if (FT_New_Face(ft, "res/fonts/Hack-Regular.ttf", 0, &face)) {
        std::cerr<<"ERROR::FREETYPE: Failed to load font"<<std::endl;
        return -1;
    }

    if (FT_Set_Pixel_Sizes(face, 0, 48)) {
        std::cerr<<"ERROR::FREETYPE: Failed to set pixel sizes"<<std::endl;
        return -1;
    }

    // disable byte alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr<<"ERROR::FREETYPE: Failed to load Glyth "<<c<<std::endl;
            return -1;
        }

        // Generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return 0;
}