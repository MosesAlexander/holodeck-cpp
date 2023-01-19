#ifndef UNIFORM_HEADERFILE_H
#define UNIFORM_HEADERFILE_H

enum class uniform_type {
    Uniform3FParam,
    Uniform1IParam,
    Uniform1FParam,
    Uniform4FVMatrix,
};

struct Uniform3FParam {
    float param[3];
};

struct Uniform1IParam {
    int32_t param;
};

struct Uniform1FParam {
    float param;
};

struct Uniform4FVMatrix {
    //Mat4 param;
};

struct UniformPackedParam {
    uniform_type type;
    union {
        float param3f[3];
        int param1i;
        float param1f;
        float parammat4[16];
    };
};

struct UniformDescriptor {
    GLint uniform_shader_handle;

    UniformDescriptor(GLuint program_id, char *uniform_name);
    void update(UniformPackedParam *packed_param);
};

#endif