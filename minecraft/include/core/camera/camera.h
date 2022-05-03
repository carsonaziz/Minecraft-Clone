#pragma once

#include <glm/glm.hpp>

namespace Minecraft
{
    class Camera
    {
    private:
        float m_fov;
        int m_width;
        int m_height;

        glm::mat4 m_projection;
        glm::mat4 m_view;

    public:
        Camera(float fov, int width, int height, glm::vec3 position);
        ~Camera();

        void set_view(const glm::vec3& position, const glm::vec3& look_at);
        inline const glm::mat4& get_view() { return m_view; }

        inline const glm::mat4& get_projection() { return m_projection; }
    };
}