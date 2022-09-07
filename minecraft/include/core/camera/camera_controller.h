#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "camera.h"

namespace Minecraft
{
    class CameraController
    {
    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_forward_direction;

        float m_speed = 7.5f;

        std::shared_ptr<Camera> m_camera;

        glm::vec2 m_mouse_previous;

    public:
        CameraController(const glm::vec3& position = glm::vec3(0, 0, 10));
        ~CameraController() {}

        void update(float dt);
        void on_event();

        inline const std::shared_ptr<Camera>& get_camera() { return m_camera; }
        void calculate_forward_direction(const glm::vec2& delta, bool& moved);
        void calculate_position(bool& moved, float dt);
    };
}