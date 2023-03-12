#ifndef VAO_HEADERFILE_H
#define VAO_HEADERFILE_H

#include "BufferDescriptor.hpp"
#include "EboDescriptor.hpp"
#include "Attributes.hpp"
#include "Holodeck.hpp"

struct EboDescriptor;

struct VaoDescriptor {
    GLuint vao_id;
    BufferDescriptor *buffer_ref;
    EboDescriptor *ebo_desc;

    VaoDescriptor(AttributesDescriptor *attr, BufferDescriptor *buffer);
    void bind();

    template <typename T>
    int set_attributes(AttributesDescriptor *attr);
    void attach_ebo(EboDescriptor *ebo);
};

#endif