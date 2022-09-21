#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "core/render/shader.h"
#include "core/utils/debug/gizmo.h"

namespace Minecraft
{
    class GizmoRenderer
    {
    private:
        std::shared_ptr<Shader> m_shader;

        glm::mat4 m_model;
        glm::mat4 m_view;
        glm::mat4 m_projection;

    public:
        GizmoRenderer();
        ~GizmoRenderer() {}

        void update();
        void render(Gizmo& gizmo);
    };
}