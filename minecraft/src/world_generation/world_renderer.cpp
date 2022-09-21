#include "world_generation/world_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/render/renderer.h"

namespace Minecraft
{
    WorldRenderer::WorldRenderer()
    {
        m_shader = std::make_shared<Shader>("minecraft/res/shaders/vertex_shader.vs", "minecraft/res/shaders/fragment_shader.fs");
    }

    WorldRenderer::~WorldRenderer() {}

    void WorldRenderer::render(std::shared_ptr<World>& world, std::shared_ptr<CameraController>& camera_controller) const
    {
        m_shader->use();
        m_shader->load_mat4(camera_controller->get_camera()->get_view(), "view");
        m_shader->load_mat4(camera_controller->get_camera()->get_projection(), "projection");

        glm::mat4 model = glm::mat4(1.0f);

        for (auto& chunk_data : world->get_chunks())
        {
            Chunk* chunk = chunk_data.second;
            model = glm::translate(model, glm::vec3(chunk->get_position().x, 0, chunk->get_position().y));
            m_shader->load_mat4(model, "model");
            model = glm::mat4(1.0f);

            Render::render(chunk->get_mesh()->get_vao(), RM_TRIANGLES);
        }
    }
}