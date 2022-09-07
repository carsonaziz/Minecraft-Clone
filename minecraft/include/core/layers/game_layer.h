#pragma once

#include "layer.h"

#include "core/camera/camera_controller.h"
#include "core/render/texture.h"
#include "world_generation/world.h"
#include "world_generation/world_renderer.h"
#include "core/events/mouse_event.h"

namespace Minecraft
{
    class GameLayer : public Layer
    {
    private:
        std::shared_ptr<World> m_world;
        std::shared_ptr<Texture> m_texture_atlas;

        std::shared_ptr<CameraController> m_camera_controller;
        std::shared_ptr<WorldRenderer> m_world_renderer;

    public:
        GameLayer();

        virtual void on_attach() override;
        virtual void on_detach() override {}
        virtual void on_event(Event& event) override;
        virtual void update(float dt) override;
        virtual void render() override;

        bool mouse_button_pressed(MouseButtonEvent& event);
    };
}