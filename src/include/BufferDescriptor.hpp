#ifndef BUFFERDESCRIPTOR_HEADERFILE_H
#define BUFFERDESCRIPTOR_HEADERFILE_H

#include "Application.hpp"

using namespace std;

struct BufferDescriptor {
    GLuint buffer_id;

    BufferDescriptor(vector<float> *vertices);
    void bind();
};
#endif