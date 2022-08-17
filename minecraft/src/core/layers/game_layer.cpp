#include "core/layers/game_layer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/render/vertex_array.h"
#include "core/render/buffer.h"
#include "core/render/shader.h"
#include "world_generation/chunk.h"

namespace Minecraft
{
    GameLayer::GameLayer() : Layer()
    {
        // load texture atlas
        m_texture_atlas = std::make_shared<Texture>();
        m_texture_atlas->bind();
        m_texture_atlas->load_data("minecraft/res/texture_atlas.png");
        m_texture_atlas->unbind();

        m_world = std::make_shared<World>();

        m_camera_controller = std::make_shared<CameraController>(glm::vec3(0, 0, 20));
        m_world_renderer = std::make_shared<WorldRenderer>();
    }

    void GameLayer::on_event(Event& event) {}

    void GameLayer::update(float dt)
    {
        m_camera_controller->update(dt);
        m_world->update();
    }

    void GameLayer::render()
    {
        m_texture_atlas->bind();
        m_world_renderer->render(m_world, m_camera_controller);
    }
}