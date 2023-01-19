#include "Application.hpp"

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
        Uniform3FParam param3f;
        Uniform1IParam param1i;
        Uniform1FParam param1f;
        Uniform4FVMatrix parammat4;
    };
};

struct UniformDescriptor {
    GLint uniform_shader_handle;
};