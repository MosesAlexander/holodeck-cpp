#include "Cube.hpp"

Cube::Cube(float side_length, float *center) {
    ScaleFactor scale_factor = { 1.0f, 1.0f };

    vertices.reserve((3 + 2) * 3 * 6);

    vector<float> temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_A);
    vector<float> temp_tex = generate_texture_coords(TextureCorner::TopLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_A);
    temp_tex = generate_texture_coords(TextureCorner::TopRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));
    
    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_A);
    temp_tex = generate_texture_coords(TextureCorner::TopRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_B);
    temp_tex = generate_texture_coords(TextureCorner::TopRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_B);
    temp_tex = generate_texture_coords(TextureCorner::TopLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_B);
    temp_tex = generate_texture_coords(TextureCorner::TopLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_C);
    temp_tex = generate_texture_coords(TextureCorner::BottomLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_C);
    temp_tex = generate_texture_coords(TextureCorner::BottomRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_C);
    temp_tex = generate_texture_coords(TextureCorner::TopLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_D);
    temp_tex = generate_texture_coords(TextureCorner::BottomRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_D);
    temp_tex = generate_texture_coords(TextureCorner::BottomLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_D);
    temp_tex = generate_texture_coords(TextureCorner::TopRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_E);
    temp_tex = generate_texture_coords(TextureCorner::TopRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_E);
    temp_tex = generate_texture_coords(TextureCorner::TopLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_E);
    temp_tex = generate_texture_coords(TextureCorner::BottomRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_F);
    temp_tex = generate_texture_coords(TextureCorner::TopLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_F);
    temp_tex = generate_texture_coords(TextureCorner::TopRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_F);
    temp_tex = generate_texture_coords(TextureCorner::BottomLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_G);
    temp_tex = generate_texture_coords(TextureCorner::BottomRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_G);
    temp_tex = generate_texture_coords(TextureCorner::BottomLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_G);
    temp_tex = generate_texture_coords(TextureCorner::BottomLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_H);
    temp_tex = generate_texture_coords(TextureCorner::BottomLeft, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_H);
    temp_tex = generate_texture_coords(TextureCorner::BottomRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    temp_coord = generate_cube_corner_coords(center, side_length, CubeCorner::COORDS_H);
    temp_tex = generate_texture_coords(TextureCorner::BottomRight, scale_factor);
    vertices.insert(std::end(vertices), std::begin(temp_coord), std::end(temp_coord));
    vertices.insert(std::end(vertices), std::begin(temp_tex), std::end(temp_tex));

    indices = {
        0, 3, 9, 0, 9, 6, // first face
        12, 15, 21, 12, 21, 18, // second face
        2, 5, 17, 2, 17, 14, // third face
        8, 11, 23, 8, 23, 20, // fourth face
        1, 13, 19, 1, 19, 7, // fifth face
        4, 16, 22, 4, 22, 10, // sixth face
    };
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


vector<float> Cube::generate_cube_corner_coords(
            float *center_point,
            float side_length,
            CubeCorner cube_corner) {
    vector<float> coords = {0.0f, 0.0f, 0.0f};

    switch(cube_corner) {
        case CubeCorner::COORDS_A:
        coords[0] = center_point[0] + side_length / 2.0f;
        coords[1] = center_point[1] + side_length / 2.0f;
        coords[2] = center_point[2] - side_length / 2.0f;
        break;
        case CubeCorner::COORDS_B:
        coords[0] = center_point[0] - side_length / 2.0f;
        coords[1] = center_point[1] + side_length / 2.0f;
        coords[2] = center_point[2] - side_length / 2.0f;
        break;
        case CubeCorner::COORDS_C:
        coords[0] = center_point[0] + side_length / 2.0f;
        coords[1] = center_point[1] - side_length / 2.0f;
        coords[2] = center_point[2] - side_length / 2.0f;
        break;
        case CubeCorner::COORDS_D:
        coords[0] = center_point[0] - side_length / 2.0f;
        coords[1] = center_point[1] - side_length / 2.0f;
        coords[2] = center_point[2] - side_length / 2.0f;
        break;
        case CubeCorner::COORDS_E:
        coords[0] = center_point[0] + side_length / 2.0f;
        coords[1] = center_point[1] + side_length / 2.0f;
        coords[2] = center_point[2] + side_length / 2.0f;
        break;
        case CubeCorner::COORDS_F:
        coords[0] = center_point[0] - side_length / 2.0f;
        coords[1] = center_point[1] + side_length / 2.0f;
        coords[2] = center_point[2] + side_length / 2.0f;
        break;
        case CubeCorner::COORDS_G:
        coords[0] = center_point[0] + side_length / 2.0f;
        coords[1] = center_point[1] - side_length / 2.0f;
        coords[2] = center_point[2] + side_length / 2.0f;
        break;
        case CubeCorner::COORDS_H:
        coords[0] = center_point[0] - side_length / 2.0f;
        coords[1] = center_point[1] - side_length / 2.0f;
        coords[2] = center_point[2] + side_length / 2.0f;
        break;
    }

    return std::move(coords);
}