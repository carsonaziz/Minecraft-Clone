#pragma once

#include "layer.h"

#include "core/log.h"
#include "core/render/renderer.h"
#include "core/camera/camera_controller.h"
#include "core/events/mouse_event.h"

namespace Minecraft
{
    class GameLayer : public Layer
    {
    private:
        std::shared_ptr<CameraController> m_camera_controller;

    public:
        GameLayer();

        virtual void on_event(Event& event) override;
        virtual void update() override;
        virtual void render(std::shared_ptr<Renderer>& renderer) override;
    };
}