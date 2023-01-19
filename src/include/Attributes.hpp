#ifndef ATTR_HEADERFILE_H
#define ATTR_HEADERFILE_H

#include "Application.hpp"

struct AttributesDescriptor {
    GLuint component_groups;
    vector<GLint> component_nums;
    vector<GLenum> component_types;
    vector<uint32_t> component_offsets;
    vector<GLint> component_strides;
};

#endif