#include <shader.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

std::string Shader::read_file(const char* path)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return stream.str();
    }
    catch(const std::exception& e)
    {
        std::cerr << "File Read Error: " << e.what() << std::endl;
    }
    return "";
}
GLuint Shader::create_shader(GLenum type, const std::string &code)
{
    int success;
    const char * source = code.c_str();
    GLuint shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
        std::cerr << "Create Shader Error(" << type << ") :" << infoLog << std::endl;
    }
    return shader_id;
}
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    GLuint vertex = create_shader(GL_VERTEX_SHADER, read_file(vertexPath));
    GLuint fragment = create_shader(GL_FRAGMENT_SHADER, read_file(fragmentPath));
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Link Program Error :" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}
void Shader::use()
{
    glUseProgram(shaderProgram);
}
void Shader::set_uniform(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void Shader::set_uniform(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void Shader::set_uniform(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void Shader::set_uniform(const std::string &name, float v1, float v2) const
{
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2);
}
void Shader::set_uniform(const std::string &name, float v1, float v2, float v3, float v4) const
{
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2, v3, v4);
}