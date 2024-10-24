#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) 
{
    const std::string vertex_source = read_shader_source("shader/" + vertex_path);
    const std::string fragment_source = read_shader_source("shader/" + fragment_path);
    program_id = create_shader_program(vertex_source.c_str(), fragment_source.c_str());
}

void Shader::use_shader() 
{
    glUseProgram(program_id);
}

GLuint Shader::get_program_id() const
{
    return program_id;
}


//read shader source code from a file
std::string Shader::read_shader_source(const std::string& file_path) 
{
    std::string code;
    std::ifstream shader_file(file_path, std::ios::in);
    
    if(shader_file.is_open()) 
    {
        std::stringstream stream;
        stream << shader_file.rdbuf();
        code = stream.str();
        shader_file.close();
    } else 
    {
        std::cerr << "Could not read file " << file_path << std::endl;
    }
    return code;
}

//utility function to compile a shader
GLuint Shader::compile_shader(GLenum type, const std::string& source) 
{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    //check for compilation errors
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    
    if(result == GL_FALSE) 
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> info_log(length);
        glGetShaderInfoLog(shader, length, nullptr, info_log.data());
        std::cerr << "Shader compilation failed: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment`") << info_log.data() << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

//utility function to create a shader program
GLuint Shader::create_shader_program(const std::string& vertex_source, const std::string& fragment_source) 
{
    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);

    if (vertex_shader == 0 || fragment_shader == 0) return 0;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glValidateProgram(program);

    //check for linking errors
    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    
    if(result == GL_FALSE) 
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> info_log(length);
        glGetProgramInfoLog(program, length, nullptr, info_log.data());
        std::cerr << "Program linking failed: " << info_log.data() << std::endl;
        glDeleteProgram(program);
        return 0;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}