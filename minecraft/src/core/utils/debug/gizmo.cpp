#include "core/utils/debug/gizmo.h"

#include <glm/gtc/matrix_transform.hpp>

#include "core/application.h"
#include "core/render/renderer.h"

namespace Minecraft
{
    Gizmo::Gizmo()
    {
        m_x_axis = std::make_shared<Line>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        m_y_axis = std::make_shared<Line>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_z_axis = std::make_shared<Line>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }
}