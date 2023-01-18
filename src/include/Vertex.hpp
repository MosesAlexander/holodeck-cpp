#include "Application.hpp"
#include "Buffer.hpp"
#include "Texture.hpp"
#include "Uniform.hpp"

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

struct AttributesDescriptor {
    GLuint component_groups;
    vector<GLint> component_nums;
    vector<GLenum> component_types;
    vector<uint32_t> component_offsets;
    vector<GLint> component_strides;
}
