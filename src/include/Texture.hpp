#ifndef TEXTURE_HEADERFILE_H
#define TEXTURE_HEADERFILE_H

#include "Holodeck.hpp"



struct TextureDescriptor {
    GLuint texture_id;
    GLint texture_shader_handle;

    TextureDescriptor(GLuint bound_program_id,
                        const char *shader_handle_name,
                        const char *path,
                        GLenum format);
    
    void set_active_texture(uint32_t idx);
};

#endif