#include "Program.hpp"

Program::Program() {
    id = glCreateProgram();
    // will increase this later when we have more
    // shaders than just vertex and fragment shader
    shader_ids.reserve(2); 
};

Program::~Program() {
    glDeleteProgram(id);
}

void Program::add_shader(Shader *shader) {
    shader_ids.push_back(shader->id);
}

int Program::link_shaders() {
    for (auto shader : shader_ids) {
        glAttachShader(id, shader);
    }

    glLinkProgram(id);

    GLint success = 1;

    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (success == 0) {
        GLint len = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
        char *error = (char*) malloc(len);

        glGetProgramInfoLog(id,
                        len,
                        NULL,
                        error
        );

        std::cerr<<"Error linking program:"<<endl<<error<<endl;
        free(error);

        throw application_exception("Failed to compile shader!");
    }

    for (auto shader : shader_ids) {
        glDetachShader(id, shader);
    }
}