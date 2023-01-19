#include "Vertex.hpp"

void Model::add_mesh(Mesh&& mesh) {
    meshes.push_back(std::move(mesh));
}

void Model::attach_program(Program *program) {
    program = program;
}

void Model::render() {
    for (auto mesh : meshes) {
        glDrawElements(
            GL_TRIANGLES,
            mesh.ebo->num_ebo_elements,
            GL_UNSIGNED_INT,
            NULL
        );
    }
}

void Model::use_program() {
    glUseProgram(program->id);
}