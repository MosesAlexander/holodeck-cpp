#ifndef BUFFER_HEADERFILE_H
#define BUFFER_HEADERFILE_H

#include "Attributes.hpp"
#include "Application.hpp"

struct BufferDescriptor {
    GLuint buffer_id;

    BufferDescriptor(vector<float> *vertices);
    void bind();
};

struct EboDescriptor {
    GLuint ebo_id;
    int num_ebo_elements;
    vector<uint32_t> ebo_indices;

    EboDescriptor(vector<uint32_t> *indices);
    void bind();
};

struct VaoDescriptor {
    GLuint vao_id;
    BufferDescriptor *buffer_ref;
    EboDescriptor *ebo_desc;

    VaoDescriptor(AttributesDescriptor *attr, BufferDescriptor *buffer);
    void bind();

    template <typename T>
    int set_attributes(AttributesDescriptor *attr);
};

#endif