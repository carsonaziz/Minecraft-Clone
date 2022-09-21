#include "core/layers/debug_layer.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "core/log.h"
#include "core/render/shader.h"
#include "core/render/buffer.h"
#include "core/render/vertex_array.h"
#include "core/render/renderer.h"
#include "core/utils/debug/debug.h"
#include "core/utils/debug/debug_renderer.h"

namespace Minecraft
{
    DebugLayer::DebugLayer()
    {
        Debug::init();
        DebugRender::init();
    }

    DebugLayer::~DebugLayer()
    {
        Debug::shutdown();
        DebugRender::shutdown();
    }

    void DebugLayer::on_event(Event& event) {}

    void DebugLayer::update(float dt) 
    {
        m_gizmo_renderer.update();
    }

    void DebugLayer::render()
    {
        Render::RenderStats& stats = Render::get_stats();

        Debug::text("Minecraft v1.0.0");
        Debug::text("FPS: %d", stats.frames);
        Debug::text("ms/frame: %.2f", stats.ms_for_frame);
        Debug::text("Triangles: %d", stats.triangle_count);
        Debug::text("%s", stats.renderer.c_str());
        Debug::text("%s", stats.gl_version.c_str());
        Debug::text("Facing: %.3f, %.3f, %.3f", stats.forward_direction.x, stats.forward_direction.y, stats.forward_direction.z);
        Debug::text("X: %.3f Y: %.3f Z: %.3f", stats.position.x, stats.position.y, stats.position.z);

        Debug::render();

        m_gizmo_renderer.render(m_gizmo);
    }
}