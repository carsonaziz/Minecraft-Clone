#include "core/camera/camera_controller.h"

// TEMP (used for keycode, mouse button codes, will make custom key and mouse codes)
#include <glfw/glfw3.h>

#include "core/input.h"

namespace Minecraft
{
    CameraController::CameraController(const glm::vec3& position) : m_position(position)
    {
        m_camera = std::make_shared<Camera>(45, 1280, 720, position);
    }

    void CameraController::update()
    {
        if (Input::is_key_down(GLFW_KEY_W))
            m_position.z -= m_movement_speed;
        if (Input::is_key_down(GLFW_KEY_S))
            m_position.z += m_movement_speed;
        if (Input::is_key_down(GLFW_KEY_A))
            m_position.x -= m_movement_speed;
        if (Input::is_key_down(GLFW_KEY_D))
            m_position.x += m_movement_speed;
        if (Input::is_key_down(GLFW_KEY_LEFT_SHIFT))
            m_position.y -= m_movement_speed;
        if (Input::is_key_down(GLFW_KEY_SPACE))
            m_position.y += m_movement_speed;

        m_camera->set_view(m_position);
    }
}