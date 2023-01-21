#ifndef EBO_HEADERFILE_H
#define EBO_HEADERFILE_H

#include "Application.hpp"
using namespace std;

struct EboDescriptor {
    GLuint ebo_id;
    int num_ebo_elements;
    vector<uint32_t> ebo_indices;

    EboDescriptor(vector<uint32_t> *indices);
    void bind();
};

#endif