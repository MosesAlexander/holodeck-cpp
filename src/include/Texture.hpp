#ifndef TEXTURE_HEADERFILE_H
#define TEXTURE_HEADERFILE_H

#include "Application.hpp"



struct TextureDescriptor {
    GLuint texture_id;
    GLint texture_shader_handle;

    TextureDescriptor(GLuint bound_program_id,
                        char *shader_handle_name,
                        char *path,
                        GLenum format);
    
    void set_active_texture(uint32_t idx);
};

#endif