#include "core/camera/camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Minecraft
{
    Camera::Camera(float fov, int width, int height, glm::vec3 position) : m_fov(fov), m_width(width), m_height(height)
    {
        m_projection = glm::perspective(fov, (float)width/(float)height, 0.1f, 1000.0f);
        m_view = glm::lookAt(position, position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
    }

    Camera::~Camera() {}

    void Camera::set_view(const glm::vec3& position, const glm::vec3& look_at)
    {
        // m_view = glm::lookAt(position, position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        m_view = glm::lookAt(position, position + look_at, glm::vec3(0, 1, 0));
    }
}