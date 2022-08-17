#include "core/camera/camera_controller.h"

// TEMP (used for keycode, mouse button codes, will make custom key and mouse codes)
#include <glfw/glfw3.h>

#include "core/input.h"
#include "core/log.h"

namespace Minecraft
{
    CameraController::CameraController(const glm::vec3& position) : m_position(position), m_rotation(glm::vec3(M_PI, 0, 0))
    {
        m_camera = std::make_shared<Camera>(position);
    }

    void CameraController::update(float dt)
    {
        // Increase rotation
        if (Input::is_key_down(GLFW_KEY_UP))
            m_rotation.x -= m_look_speed * dt;
        if (Input::is_key_down(GLFW_KEY_DOWN))
            m_rotation.x += m_look_speed * dt;
        if (Input::is_key_down(GLFW_KEY_RIGHT))
            m_rotation.y -= m_look_speed * dt;
        if (Input::is_key_down(GLFW_KEY_LEFT))
            m_rotation.y += m_look_speed * dt;

        // Calculate look_at vector
        m_look_at.x = glm::cos(m_rotation.x) * glm::sin(m_rotation.y);
        m_look_at.y = glm::sin(m_rotation.x);
        m_look_at.z = glm::cos(m_rotation.x) * glm::cos(m_rotation.y);

        float normalized_xz = glm::sqrt((m_look_at.x * m_look_at.x) + (m_look_at.z * m_look_at.z));

        // calculate position for key pressed, taking into account where the camera is looking
        // normalized_xz is used so that movement speed doesn't slow when looking down or up
        if (Input::is_key_down(GLFW_KEY_W))
        {
            m_position.x += m_look_at.x / normalized_xz * m_look_speed * dt;
            m_position.z += m_look_at.z / normalized_xz * m_look_speed * dt;
        }
        if (Input::is_key_down(GLFW_KEY_S))
        {
            m_position.x -= m_look_at.x / normalized_xz * m_look_speed * dt;
            m_position.z -= m_look_at.z / normalized_xz * m_look_speed * dt;
        }
        if (Input::is_key_down(GLFW_KEY_A))
        {
            m_position.x += m_look_at.z / normalized_xz * m_look_speed * dt;
            m_position.z -= m_look_at.x / normalized_xz * m_look_speed * dt;
        }
        if (Input::is_key_down(GLFW_KEY_D))
        {
            m_position.x -= m_look_at.z / normalized_xz * m_look_speed * dt;
            m_position.z += m_look_at.x / normalized_xz * m_look_speed * dt;
        }
        if (Input::is_key_down(GLFW_KEY_LEFT_SHIFT))
        {
            m_position.y -= m_look_speed * dt;
        }
        if (Input::is_key_down(GLFW_KEY_SPACE))
        {
            m_position.y += m_look_speed * dt;
        }

        m_camera->set_view(m_position, m_look_at);
    }
}