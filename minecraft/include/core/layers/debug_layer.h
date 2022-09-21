#pragma once

#include "layer.h"

#include "core/utils/debug/gizmo.h"
#include "core/utils/debug/gizmo_renderer.h"

namespace Minecraft
{
    class DebugLayer : public Layer
    {
    private:
        Gizmo m_gizmo;
        GizmoRenderer m_gizmo_renderer;
    public:
        DebugLayer();
        ~DebugLayer();

        virtual void on_attach() override {}
        virtual void on_detach() override {}
        virtual void on_event(Event& event) override;
        virtual void update(float dt) override;
        virtual void render() override;
    };
}