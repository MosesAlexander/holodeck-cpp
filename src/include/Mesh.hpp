#ifndef MESH_HEADERFILE_H
#define MESH_HEADERFILE_H

#include "BufferDescriptor.hpp"
#include "Application.hpp"
#include "VaoDescriptor.hpp"
#include "Texture.hpp"
#include "Program.hpp"
#include "Attributes.hpp"
#include "Uniform.hpp"

using namespace std;

struct BufferDescriptor;
struct VaoDescriptor;
struct EboDescriptor;
struct UniformDescriptor;
struct TextureDescriptor;

struct Mesh {
    vector<float> vertices;
    vector<uint32_t> *indices;
    vector<TextureDescriptor> textures;
    vector<UniformDescriptor> uniforms;
    BufferDescriptor *m_buffer;
    VaoDescriptor *m_vao;
    EboDescriptor *m_ebo;

    Mesh(vector<float> *vertices, vector<uint32_t> *indices,
                        AttributesDescriptor *attr);
    ~Mesh();
    Mesh(Mesh&& source);
    Mesh& operator=(Mesh&& source);
    Mesh(const Mesh&) = delete;
    const Mesh& operator=(const Mesh&) = delete;
    void bind_vao();
    void add_uniform(UniformDescriptor&& uniform);
    void add_texture(TextureDescriptor&& texture);
    void render();
};

#endif