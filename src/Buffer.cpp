#include "Buffer.hpp"
#include "Vertex.hpp"

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

VaoDescriptor::VaoDescriptor(AttributesDescriptor *attr,
                            BufferDescriptor *buffer) {
    glGenVertexArrays(1, &vao_id);

    buffer->bind();
    buffer_ref = buffer;
    bind();
    ebo_desc = nullptr;

    int ret = 0;
    ret = set_attributes(attr);
    if(ret < 0) {
        cerr<<"Failure to set attributes to VAO"<<endl;
        throw application_exception("Failure to set attributes to VAO");
    }
}

void VaoDescriptor::bind() {
    glBindVertexArray(vao_id);
}

template<typename T>
int VaoDescriptor::set_attributes(AttributesDescriptor *attr) {
    bind();
    buffer_ref->bind();

    for (auto attr_idx : attr->component_groups) {
        glVertexAttribPointer(
            attr_idx,
            attr->component_nums[attr_idx],
            attr->component_types[attr_idx],
            GL_FALSE,
            attr->component_strides[attr_idx] * sizeof(T),
            attr->component_offsets[attr_idx] * sizeof(T)
        );
        glEnableVertexArrayAttrib(attr_idx);
    }
}