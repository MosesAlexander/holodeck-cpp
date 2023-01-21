#include "EboDescriptor.hpp"

EboDescriptor::EboDescriptor(vector<uint32_t> *indices) {
    glGenBuffers(1, &ebo_id);
    bind();
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices->size() * sizeof(uint32_t),
        indices->data(),
        GL_STATIC_DRAW
    );
}

void EboDescriptor::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
}