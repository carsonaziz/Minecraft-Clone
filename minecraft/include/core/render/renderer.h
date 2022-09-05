#pragma once

#include <string>

#include "vertex_array.h"
#include "world_generation/chunk.h"

namespace Minecraft
{
    namespace Render
    {
        struct RenderStats
        {
            int triangle_count;
            int frames;
            float ms_for_frame;
            std::string vendor;
            std::string renderer;
            std::string gl_version;

            RenderStats() : triangle_count(0), frames(0), ms_for_frame(0), vendor((char*)glGetString(GL_VENDOR)), renderer((char*)glGetString(GL_RENDERER)), gl_version((char*)glGetString(GL_VERSION)) {}
        };

        struct RenderInfo
        {
            RenderStats stats;
            int render_mode;

            RenderInfo() : render_mode(GL_FILL) {}
        };

        void init();
        RenderStats& get_stats();
        void toggle_render_mode();
        void clear();
        void render(std::shared_ptr<VertexArray> vao);
    };
}