#include "core/layers/game_layer.h"

#include <glm/glm.hpp>
// TEMP replace with custom keycodes
#include <glfw/glfw3.h>

#include "core/log.h"
#include "core/render/vertex_array.h"
#include "core/render/buffer.h"
#include "core/render/shader.h"
#include "world_generation/chunk.h"
#include "core/application.h"
#include "core/input.h"

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

        m_camera_controller = std::make_shared<CameraController>(glm::vec3(0, 250, 20));
        m_world_renderer = std::make_shared<WorldRenderer>();
    }

    void GameLayer::on_attach()
    {
    }

    void GameLayer::on_event(Event& event)
    {
        EventHandler handler(event);
        handler.handle_event<MouseButtonPressedEvent>(std::bind(&GameLayer::mouse_button_pressed, this, std::placeholders::_1));
    }

    bool GameLayer::mouse_button_pressed(MouseButtonEvent& event)
    {
        if (event.get_mouse_button() == GLFW_MOUSE_BUTTON_1)
        {
            Input::toggle_cursor();
        }
        return true;
    }

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