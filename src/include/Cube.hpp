#ifndef CUBE_HEADERFILE_H
#define CUBE_HEADERFILE_H

#include "Application.hpp"

enum class CubeCorner {
    COORDS_A,
    COORDS_B,
    COORDS_C,
    COORDS_D,
    COORDS_E,
    COORDS_F,
    COORDS_G,
    COORDS_H
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
    vector<float> generate_cube_corner_coords(float *center_point, float side_length, CubeCorner cube_corner);
};

#endif