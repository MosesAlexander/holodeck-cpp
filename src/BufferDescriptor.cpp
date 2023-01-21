//#include "BufferDescriptor.hpp"
#include "VaoDescriptor.hpp"

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