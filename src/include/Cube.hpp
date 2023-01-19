#ifndef CUBE_HEADERFILE_H
#define CUBE_HEADERFILE_H

#include "Application.hpp"

struct TextureCoords {
    float x;
    float y;
};

struct ScaleFactor {
    float x;
    float y;
};

enum class TextureCorner {
    BottomLeft,
    BottomRight,
    TopLeft,
    TopRight
};

struct Cube {
    vector<float> vertices;
    vector<uint32_t> indices;
    float center[3];

    Cube(float side_length, float *center);
    vector<float> generate_texture_coords(TextureCorner texture_corner, ScaleFactor scale_factor);
};

#endif