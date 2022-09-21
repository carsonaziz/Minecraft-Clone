#include "core/camera/camera_controller.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

// TEMP (used for keycode, mouse button codes, will make custom key and mouse codes)
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include "core/input.h"
#include "core/log.h"
#include "core/render/renderer.h"

namespace Minecraft
{
    CameraController::CameraController(const glm::vec3& position) : m_position(position), m_rotation(glm::vec3(0, 0, 0)), m_forward_direction(glm::vec3(0, 0, 1))
    {
        m_camera = std::make_shared<Camera>(position);
    }

    void CameraController::update(float dt)
    {
        bool moved = false;

        // get mouse position delta
        glm::vec2 mouse_pos = Input::get_mouse_pos();
        glm::vec2 delta = (mouse_pos - m_mouse_previous);
        m_mouse_previous = mouse_pos;

        calculate_position(moved, dt);
        calculate_forward_direction(delta, moved);

        if (moved) m_camera->set_view(m_position, m_forward_direction);
    }

    void CameraController::calculate_position(bool& moved, float dt)
    {
        // position moves based on x and z looking direction
        // x and z are normalized without y position so that looking up or down does not change movement speed
        float normalized_xz = glm::sqrt((m_forward_direction.x * m_forward_direction.x) + (m_forward_direction.z * m_forward_direction.z));
        float normalized_forward_x = m_forward_direction.x / normalized_xz;
        float normalized_forward_z = m_forward_direction.z / normalized_xz;

        if (Input::is_key_down(GLFW_KEY_W))
        {
            m_position.x += normalized_forward_x * m_speed * dt;
            m_position.z += normalized_forward_z * m_speed * dt;
            moved = true;
        }
        if (Input::is_key_down(GLFW_KEY_S))
        {
            m_position.x -= normalized_forward_x * m_speed * dt;
            m_position.z -= normalized_forward_z * m_speed * dt;
            moved = true;
        }
        if (Input::is_key_down(GLFW_KEY_A))
        {
            m_position.x += normalized_forward_z * m_speed * dt;
            m_position.z -= normalized_forward_x * m_speed * dt;
            moved = true;
        }
        if (Input::is_key_down(GLFW_KEY_D))
        {
            m_position.x -= normalized_forward_z * m_speed * dt;
            m_position.z += normalized_forward_x * m_speed * dt;
            moved = true;
        }
        if (Input::is_key_down(GLFW_KEY_LEFT_SHIFT))
        {
            m_position.y -= m_speed * dt;
            moved = true;
        }
        if (Input::is_key_down(GLFW_KEY_SPACE))
        {
            m_position.y += m_speed * dt;
            moved = true;
        }
    }

    void CameraController::calculate_forward_direction(const glm::vec2& delta, bool& moved)
    {
        float pitch_delta = delta.y * 0.5f;
        float yaw_delta = delta.x * 0.5f;
        
        if (delta.x != 0.0f || delta.y != 0.0f)
        {
            float y = glm::radians(pitch_delta);
            float x = glm::radians(yaw_delta);

            // stop camera rotation from going past directly up or directly down
            if (!(m_rotation.y - y > 3.14f/2.0f || m_rotation.y - y < -3.14f/2.0f)) m_rotation.y -= y;
            m_rotation.x += x;

            m_forward_direction.x = glm::cos(m_rotation.x) * glm::cos(m_rotation.y);
            m_forward_direction.y = glm::sin(m_rotation.y);
            m_forward_direction.z = glm::sin(m_rotation.x) * glm::cos(m_rotation.y);

            moved = true;
        }

        Render::get_stats().forward_direction = m_forward_direction;
        Render::get_stats().position = m_position;
    }
}