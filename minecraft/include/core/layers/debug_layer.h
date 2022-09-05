#pragma once

#include "layer.h"

#include "core/log.h"

namespace Minecraft
{
    class DebugLayer : public Layer
    {
    private:

    public:
        DebugLayer();
        ~DebugLayer();

        virtual void on_event(Event& event) override;
        virtual void update(float dt) override;
        virtual void render() override;
    };
}