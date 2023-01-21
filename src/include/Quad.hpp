#ifndef QUAD_HEADERFILE_H
#define QUAD_HEADERFILE_H

#include "Application.hpp"
#include "Cube.hpp"

struct Quad {
    vector<float> vertices;
    vector<uint32_t> indices;
    float center[3];

    Quad(float width, float height, float *center_offset, float *center, ScaleFactor scale_factor);
};
#endif