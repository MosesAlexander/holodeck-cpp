#include "VaoDescriptor.hpp"

VaoDescriptor::VaoDescriptor(AttributesDescriptor *attr,
                            BufferDescriptor *buffer) {
    glGenVertexArrays(1, &vao_id);

    buffer->bind();
    buffer_ref = buffer;
    bind();
    ebo_desc = nullptr;

    int ret = 0;
    ret = set_attributes<float>(attr);
    if(ret < 0) {
        cerr<<"Failure to set attributes to VAO"<<endl;
        throw holodeck_exception("Failure to set attributes to VAO");
    }
}

void VaoDescriptor::bind() {
    glBindVertexArray(vao_id);
}

template<typename T>
int VaoDescriptor::set_attributes(AttributesDescriptor *attr) {
    bind();
    buffer_ref->bind();

    for (auto attr_idx = 0; attr_idx < attr->component_groups; attr_idx++) {
        glVertexAttribPointer(
            attr_idx,
            attr->component_nums[attr_idx],
            attr->component_types[attr_idx],
            GL_FALSE,
            attr->component_strides[attr_idx] * sizeof(T),
            (const void *) (attr->component_offsets[attr_idx] * sizeof(T))
        );
        glEnableVertexAttribArray(attr_idx);
    }

    return 0;
}

void VaoDescriptor::attach_ebo(EboDescriptor *ebo) {
    ebo_desc = ebo;
    buffer_ref->bind();
    bind();
    ebo_desc->bind();
}