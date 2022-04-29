#pragma once

#include "layer.h"

#include "core/log.h"
#include "core/events/key_event.h"
#include "core/render/renderer.h"

namespace Minecraft
{
    class GameLayer : public Layer
    {
    public:
        GameLayer() : Layer() {}

        virtual void on_event(Event& event) override;
        virtual void update() override {}
        virtual void render(std::shared_ptr<Renderer>& renderer) override;

        bool test(Event& event)
        {
            // MC_LOG_WARN("{}, in game", event.to_string());

            return true;
        }
    };
}