#pragma once

#include "layer.h"

#include "core/log.h"
#include "core/events/key_event.h"

namespace Minecraft
{
    class PauseMenuLayer : public Layer
    {
    public:
        PauseMenuLayer() : Layer() {}

        virtual void on_event(Event& event) override
        {
            EventHandler handler(event);
            handler.handle_event<KeyPressedEvent>(std::bind(&PauseMenuLayer::test, this, std::placeholders::_1));
        }

        virtual void render(std::shared_ptr<Renderer>& renderer) override {}
        virtual void update() override {}

        bool test(Event& event)
        {
            // MC_LOG_WARN(event.to_string());

            return true;
        }
    };
}