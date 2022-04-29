#pragma once

#include "core/events/event.h"
#include "core/render/renderer.h"

namespace Minecraft
{
    class Layer
    {
    public:
        Layer() {}
        virtual ~Layer() {}

        virtual void on_event(Event& event) = 0;
        virtual void render(std::shared_ptr<Renderer>& renderer) = 0;
        virtual void update() = 0;
    };
}