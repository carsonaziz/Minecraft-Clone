#pragma once

namespace Minecraft
{
    class Shader
    {
    private:
        unsigned int m_program;

    private:
        unsigned int create_shader(int type, const char* shader_source);
        void create_program(unsigned int vertex_shader, unsigned int fragment_shader);
    public:
        Shader(const char* vertex_source, const char* fragment_source);
        ~Shader();

        void use();
    };
}