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
        glm::vec3 m_look_at;

        float m_movement_speed = 0.125f;

        std::shared_ptr<Camera> m_camera;

    public:
        CameraController(const glm::vec3& position = glm::vec3(0, 0, 10));
        ~CameraController() {}

        void update();
        void on_event();

        inline const std::shared_ptr<Camera>& get_camera() { return m_camera; }
    };
}