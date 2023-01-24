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
}