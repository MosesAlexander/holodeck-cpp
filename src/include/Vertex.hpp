#ifndef VERTEX_HEADERFILE_H
#define VERTEX_HEADERFILE_H

#include "Buffer.hpp"
#include "Application.hpp"
#include "Texture.hpp"
#include "Uniform.hpp"
#include "Program.hpp"

struct Mesh {
    vector<float> vertices;
    vector<uint32_t> *indices;
    vector<TextureDescriptor> textures;
    vector<UniformDescriptor> uniforms;
    BufferDescriptor *buffer;
    VaoDescriptor vao;
    EboDescriptor *ebo;
};

struct Model {
    vector<Mesh> meshes;
    Program program;
};

#endif