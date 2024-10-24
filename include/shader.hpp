#pragma once 

#include <GL/glew.h>
#include <string>

class Shader 
{
public:
    Shader(const std::string& vertex_path, const std::string& fragment_path);
    void use_shader();
    GLuint get_program_id() const;
    
private:
    std::string read_shader_source(const std::string& filePath);
    GLuint compile_shader(GLenum type, const std::string& source);
    GLuint create_shader_program(const std::string& vertexSource, const std::string& fragmentSource);
    
    GLuint program_id;
};
