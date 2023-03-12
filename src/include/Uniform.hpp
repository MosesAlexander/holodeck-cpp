#ifndef UNIFORM_HEADERFILE_H
#define UNIFORM_HEADERFILE_H

//#include "Application.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class uniform_type {
    Uniform3FParam,
    Uniform1IParam,
    Uniform1FParam,
    Uniform4FVMatrix,
    Undefined
};

enum class transform_type {
    rotate_x,
    rotate_y,
    rotate_z,
    translate,
    projection,
    look_at,
    lightColor,
    mixvalue,
    textColor,
    undefined
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
    uniform_type type;
    transform_type transf_type;

    UniformDescriptor(GLuint program_id, const char *uniform_name, uniform_type type, transform_type transf_type);
    UniformDescriptor(UniformDescriptor&&);
    UniformDescriptor() : uniform_shader_handle(0) {};
    UniformDescriptor& operator=(const UniformDescriptor&);
    void update(const UniformPackedParam& packed_param);
};

#endif