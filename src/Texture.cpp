#include "Texture.hpp"

TextureDescriptor::TextureDescriptor(GLuint bound_program_id,
                    char *shader_handle_name,
                    char *path,
                    GLenum format) {
    
    int width = 0;
    int height = 0;
    int nr_channels = 0;

    texture_shader_handle = glGetUniformLocation(
        bound_program_id,
        shader_handle_name
    );

    glGenTextures(1, &texture_id);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}