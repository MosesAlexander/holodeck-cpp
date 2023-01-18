#include "Buffer.hpp"

BufferDescriptor::BufferDescriptor(vector<float> *vertices) {
    glGenBuffers(1, &buffer_id);
    bind();
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices->size() * sizeof(float),
        vertices->data(),
        GL_STATIC_DRAW
    );
}

void BufferDescriptor::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}

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