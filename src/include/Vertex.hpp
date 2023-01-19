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
    vector<TextureDescriptor*> textures;
    vector<UniformDescriptor> uniforms;
    BufferDescriptor *m_buffer;
    VaoDescriptor *m_vao;
    EboDescriptor *m_ebo;

    Mesh(vector<float> *vertices, vector<uint32_t> *indices,
                        AttributesDescriptor *attr);
    ~Mesh();
    void bind_vao();
    void add_uniform(UniformDescriptor&& uniform);
    void add_texture(TextureDescriptor *texture);
    void render();
};

struct Model {
    vector<Mesh> meshes;
    Program *program;

    void add_mesh(Mesh&& mesh);
    void attach_program(Program *program);
    void render();
    void use_program();
};

#endif