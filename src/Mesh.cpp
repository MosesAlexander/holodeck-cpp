#include "Mesh.hpp"

Mesh::Mesh(vector<float> *vertices, vector<uint32_t> *indices, AttributesDescriptor *attr) {
    BufferDescriptor *buffer = new BufferDescriptor(vertices);
    VaoDescriptor *vao = new VaoDescriptor(attr, buffer);
    EboDescriptor *ebo = new EboDescriptor(indices);
    vao->attach_ebo(ebo);

    m_buffer = buffer;
    m_vao = vao;
    m_ebo = ebo;
}

Mesh::~Mesh() {
    delete m_buffer;
    delete m_vao;
    delete m_ebo;
}

void Mesh::bind_vao() {
    m_vao->bind();
}

void Mesh::add_uniform(UniformDescriptor&& uniform) {
    uniforms.push_back(std::move(uniform));
}

void Mesh::add_texture(TextureDescriptor&& texture) {
    textures.push_back(std::move(texture));
}

void Mesh::render() {
    glDrawElements(
        GL_TRIANGLES,
        m_ebo->num_ebo_elements,
        GL_UNSIGNED_INT,
        NULL
    );
}

Mesh::Mesh(Mesh&& source) {
    this->m_buffer = source.m_buffer;
    this->m_vao = source.m_vao;
    this->m_ebo = source.m_ebo;
    this->uniforms = std::move(source.uniforms);
    this->textures = std::move(source.textures);

    source.m_buffer = nullptr;
    source.m_vao = nullptr;
    source.m_ebo = nullptr;
}

Mesh& Mesh::operator=(Mesh&& source) {
    this->m_buffer = source.m_buffer;
    this->m_vao = source.m_vao;
    this->m_ebo = source.m_ebo;

    source.m_buffer = nullptr;
    source.m_vao = nullptr;
    source.m_ebo = nullptr;

    return *this;
}

/*
Mesh::Mesh(const Mesh& source) {
    /*
    this->m_buffer = source.m_buffer;
    this->m_vao = source.m_vao;
    this->m_ebo = source.m_ebo;
}

const Mesh& Mesh::operator=(const Mesh& source) {
    return source;
}
*/