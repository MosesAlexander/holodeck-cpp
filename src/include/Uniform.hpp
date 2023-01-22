#ifndef UNIFORM_HEADERFILE_H
#define UNIFORM_HEADERFILE_H

#include "Application.hpp"

enum class uniform_type {
    Uniform3FParam,
    Uniform1IParam,
    Uniform1FParam,
    Uniform4FVMatrix,
};

struct UniformPackedParam {
    uniform_type type;
    union {
        float param3f[3];
        int param1i;
        float param1f;
        glm::mat4 parammat;
    };
};

struct UniformDescriptor {
    GLint uniform_shader_handle;

    UniformDescriptor(GLuint program_id, const char *uniform_name);
    UniformDescriptor(UniformDescriptor&&);
    UniformDescriptor& operator=(const UniformDescriptor&) = delete;
    void update(const UniformPackedParam& packed_param);
};

#endif