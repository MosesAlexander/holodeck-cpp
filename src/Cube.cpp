#include "Cube.hpp"

Cube::Cube(float side_length, float *center) {
    vector<float> vertices_cube;
    vertices_cube.reserve((3 + 2) * 3 * 6);




}

vector<float> Cube::generate_texture_coords(TextureCorner texture_corner, ScaleFactor scale_factor) {
    vector<float> texture_coords = { 0.0f, 0.0f };

    switch(texture_corner) {
        case TextureCorner::BottomLeft:
        //default
        break;
        case TextureCorner::BottomRight:
        texture_coords[0] = scale_factor.x;
        break;
        case TextureCorner::TopLeft:
        texture_coords[1] = scale_factor.y;
        break;
        case TextureCorner::TopRight:
        texture_coords[0] = scale_factor.x;
        texture_coords[1] = scale_factor.y;
        break;
    }
    
    return std::move(texture_coords);
}

