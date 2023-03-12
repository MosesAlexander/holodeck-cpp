#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureDescriptor::TextureDescriptor(GLuint bound_program_id,
                    const char *shader_handle_name,
                    const char *path,
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

    stbi_set_flip_vertically_on_load(1);
    uint8_t *buffer = stbi_load(
        path,
        &width,
        &height,
        &nr_channels,
        0
    );

    if (!buffer) {
        cerr<<"Failed to load texture!"<<endl;
        throw holodeck_exception("Failed to load texture!");
    }

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        (const void*) buffer
    );

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(buffer);
}

void TextureDescriptor::set_active_texture(uint32_t idx) {
    glActiveTexture(GL_TEXTURE0 + idx);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(texture_shader_handle, idx);
}