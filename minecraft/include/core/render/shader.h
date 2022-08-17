#pragma once

#include <glm/glm.hpp>
#include <string>

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
        Shader(const std::string& vertex_path, const std::string& fragment_path);
        ~Shader();

        void use();
        void load_float3(const glm::vec3& vec, const std::string& name);
        void load_mat4(const glm::mat4& mat, const std::string& name);
    };
}