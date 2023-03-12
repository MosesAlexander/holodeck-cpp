#include "Model.hpp"

void Model::add_mesh(Mesh&& mesh) {
    meshes.push_back(std::move(mesh));
}

void Model::attach_program(const Program &program) {
    this->program_id = program.id;
}

void Model::render() {
    for (auto &mesh : meshes) {
        glDrawElements(
            GL_TRIANGLES,
            mesh.m_ebo->num_ebo_elements,
            GL_UNSIGNED_INT,
            NULL
        );
    }
}

void Model::use_program() {
    glUseProgram(program_id);
}

Model::Model(Model&& source) {
    meshes = std::move(source.meshes);
    program_id = source.program_id;
    source.program_id = 0;
    model_name = source.model_name;
    obj_type = source.obj_type;
}

Model::Model() {
}