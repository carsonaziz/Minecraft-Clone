#include "core/utils/debug/gizmo_renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "core/render/renderer.h"

namespace Minecraft
{
    GizmoRenderer::GizmoRenderer()
    {
        m_shader = std::make_shared<Shader>("minecraft/res/shaders/gizmo_vshader.vs", "minecraft/res/shaders/gizmo_fshader.fs");

        m_model = glm::mat4(1.0f);
        m_model = glm::scale(m_model, glm::vec3(0.1f, 0.1f, 0.1f));

        m_view = glm::mat4(1.0f);
        m_view = glm::lookAt(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));

        m_projection = glm::mat4(1.0f);
        // m_projection = glm::perspective(45.0f, (float)Application::get()->get_window()->get_height() / Application::get()->get_window()->get_width(), 0.1f, 100.0f);
        m_projection = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
    }

    void GizmoRenderer::update()
    {
        constexpr glm::vec3 up_direction(0, 1, 0);

        Render::RenderStats& stats = Render::get_stats();
        m_view = glm::lookAt(-stats.forward_direction, glm::vec3(0, 0, 0.0f), up_direction);
    }

    void GizmoRenderer::render(Gizmo& gizmo)
    {
        m_shader->use();
        m_shader->load_mat4(m_model, "model");
        m_shader->load_mat4(m_view, "view");
        m_shader->load_mat4(m_projection, "projection");

        auto& x_axis = gizmo.get_x_axis();
        auto& y_axis = gizmo.get_y_axis();
        auto& z_axis = gizmo.get_z_axis();

        m_shader->load_float3(x_axis->get_color(), "color");
        Render::render(x_axis->get_vao(), RM_LINES);

        m_shader->load_float3(y_axis->get_color(), "color");
        Render::render(y_axis->get_vao(), RM_LINES);

        m_shader->load_float3(z_axis->get_color(), "color");
        Render::render(z_axis->get_vao(), RM_LINES);
    }
}