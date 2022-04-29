#include "core/render/shader.h"

#include <glad/glad.h>

#include "core/log.h"

namespace Minecraft
{
    Shader::Shader(const char* vertex_source, const char* fragment_source)
    {
        unsigned int vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source);
        unsigned int fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source);
        create_program(vertex_shader, fragment_shader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_program);
    }

    unsigned int Shader::create_shader(int type, const char* shader_source)
    {
        int success;
        char infoLog[512];
        
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &shader_source, nullptr);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            MC_LOG_ERROR("SHADER::COMPILATION_FAILED::{}", infoLog);
        };

        return shader;
    }

    void Shader::create_program(unsigned int vertex_shader, unsigned int fragment_shader)
    {
        int success;
        char infoLog[512];

        m_program = glCreateProgram();
        glAttachShader(m_program, vertex_shader);
        glAttachShader(m_program, fragment_shader);
        glLinkProgram(m_program);

        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(m_program, 512, NULL, infoLog);
            MC_LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED::{}", infoLog);
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    void Shader::use()
    {
        glUseProgram(m_program);
    }
}