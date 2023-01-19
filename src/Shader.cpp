#include "Shader.hpp"

Shader::Shader(string *source, GLenum kind) {
    std::ifstream ShaderFile;
    string ShaderCode;

    id = glCreateShader(kind);

    ShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try 
    {
        // open files
        ShaderFile.open(source->c_str());
        std::stringstream ShaderStream;
        // read file's buffer contents into streams
        ShaderStream << ShaderFile.rdbuf();
        // close file handlers
        ShaderFile.close();
        // convert stream into string
        ShaderCode = ShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* shader_code = ShaderCode.c_str();

    GLint success = 1;

    glShaderSource(id,
                1,
                &shader_code,
                NULL
    );
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (success == 0) {
        GLint len = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char *error = (char*) malloc(len);

        glGetShaderInfoLog(id,
                        len,
                        NULL,
                        error
        );

        std::cerr<<"Error compiling shader:"<<endl<<error<<endl;
        free(error);

        throw application_exception("Failed to compile shader!");
    }
}

Shader::~Shader() {
    glDeleteShader(id);
}