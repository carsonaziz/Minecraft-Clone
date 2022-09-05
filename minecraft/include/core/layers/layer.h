#pragma once

#include "core/events/event.h"

namespace Minecraft
{
    class Layer
    {
    public:
        Layer() {}
        virtual ~Layer() {}

        virtual void on_event(Event& event) = 0;
        virtual void render() = 0;
        virtual void update(float dt) = 0;
    };
}