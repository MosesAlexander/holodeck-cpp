#include "Quad.hpp"

Quad::Quad(float width, float height, float *center_offset, float *center, ScaleFactor scale_factor) {
    vector<float> temp_coords;
    vector<float> temp_tex;

    if (center[0] != 0.0f) {
        temp_coords = {center_offset[0], 0.0f, -width / 2.0f};
        temp_tex = Cube::generate_texture_coords(TextureCorner::BottomLeft, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

        temp_coords = {center_offset[0], height,  -width / 2.0f};
        temp_tex = Cube::generate_texture_coords(TextureCorner::TopLeft, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

        temp_coords = {center_offset[0], 0.0f,  width / 2.0f};
        temp_tex = Cube::generate_texture_coords(TextureCorner::BottomRight, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

        temp_coords = {center_offset[0],  height,  width / 2.0f};
        temp_tex = Cube::generate_texture_coords(TextureCorner::TopRight, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));
    } else if (center[1] != 0.0f) {
        temp_coords = {-width / 2.0f, center_offset[1], -width / 2.0f};
        temp_tex = Cube::generate_texture_coords(TextureCorner::BottomLeft, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

        temp_coords = { width / 2.0f, center_offset[1], -width / 2.0f};
        temp_tex = Cube::generate_texture_coords(TextureCorner::BottomRight, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

        temp_coords = {-width / 2.0f, center_offset[1],  width / 2.0f};
        temp_tex = Cube::generate_texture_coords(TextureCorner::TopLeft, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

        temp_coords = {width / 2.0f, center_offset[1],  width / 2.0f};
        temp_tex = Cube::generate_texture_coords(TextureCorner::TopRight, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

    } else if (center[2] != 0.0f) {
        temp_coords = {-width / 2.0f, 0.0f, center_offset[2]};
        temp_tex = Cube::generate_texture_coords(TextureCorner::BottomLeft, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

        temp_coords = { width / 2.0f,  0.0f, center_offset[2]};
        temp_tex = Cube::generate_texture_coords(TextureCorner::BottomRight, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

        temp_coords = {-width / 2.0f, height, center_offset[2]};
        temp_tex = Cube::generate_texture_coords(TextureCorner::TopLeft, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));

        temp_coords = {width / 2.0f,  height, center_offset[2]};
        temp_tex = Cube::generate_texture_coords(TextureCorner::TopRight, scale_factor);
        vertices.insert(std::begin(vertices), std::begin(temp_coords), std::end(temp_coords));
        vertices.insert(std::begin(vertices), std::begin(temp_tex), std::end(temp_tex));
    } else {
        cerr<<"ERROR: only simple offset vectors accepted"<<endl;
        throw application_exception("ERROR: only simple offset vectors accepted!");
    }

    indices = {0,1,2,1,3,2};
}