#ifndef MODEL_HEADERFILE_H
#define MODEL_HEADERFILE_H

#include "Application.hpp"
#include "Mesh.hpp"
#include "Program.hpp"

struct Program;
struct Mesh;

using namespace std;

struct Model {
    vector<Mesh> meshes;
    Program *program;

    void add_mesh(Mesh&& mesh);
    void attach_program(Program *program);
    void render();
    void use_program();
};

#endif