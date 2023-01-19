#include "Uniform.hpp"

UniformDescriptor::UniformDescriptor(GLuint program_id, char *uniform_name) {
    uniform_shader_handle = glGetUniformLocation(
        program_id,
        uniform_name
    );
}

void UniformDescriptor::update(UniformPackedParam *packedparam) {
    switch(packedparam->type)
    {
        case uniform_type::Uniform1FParam:
            glUniform1f(uniform_shader_handle, packedparam->param1f);
        break;
        case uniform_type::Uniform1IParam:
            glUniform1i(uniform_shader_handle, packedparam->param1i);
        break;
        case uniform_type::Uniform3FParam:
            glUniform3f(uniform_shader_handle,
                packedparam->param3f[0],
                packedparam->param3f[1],
                packedparam->param3f[2]
            );
        break;
        case uniform_type::Uniform4FVMatrix:
            glUniformMatrix4fv(
                uniform_shader_handle,
                1,
                GL_FALSE,
                packedparam->parammat4
            );
        break;
    }
}