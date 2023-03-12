#ifndef MODEL_HEADERFILE_H
#define MODEL_HEADERFILE_H

#include "Holodeck.hpp"
#include "Mesh.hpp"
#include "Program.hpp"
#include "JsonConfig.hpp"

struct Program;
struct Mesh;

using namespace std;

struct Model {
    vector<Mesh> meshes;
    GLuint program_id;
    string model_name;
    object_type obj_type;

    Model(Model&&);
    Model();
    Model& operator=(Model&&) = delete;
    void add_mesh(Mesh&& mesh);
    void attach_program(const Program &program);
    void render();
    void use_program();
};

#endif