#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glad/glad.h>

class Shader
{
public:
    GLuint shaderProgram;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use();
    void set_uniform(const std::string &name, bool value) const;
    void set_uniform(const std::string &name, int value) const;
    void set_uniform(const std::string &name, float value) const;
    void set_uniform(const std::string &name, float v1, float v2) const;
    void set_uniform(const std::string &name, float v1, float v2, float v3, float v4) const;
private:
    std::string read_file(const char* path);
    GLuint create_shader(GLenum type, const std::string &code);
};

#endif