#pragma once

#include <string>

#include "vertex_array.h"
#include "world_generation/chunk.h"

namespace Minecraft
{
    #define RM_TRIANGLES GL_TRIANGLES
    #define RM_LINES GL_LINES
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
            glm::vec3 forward_direction;
            glm::vec3 position;

            RenderStats() : 
                triangle_count(0), frames(0), ms_for_frame(0), 
                vendor((char*)glGetString(GL_VENDOR)), renderer((char*)glGetString(GL_RENDERER)), 
                gl_version((char*)glGetString(GL_VERSION)), forward_direction(glm::vec3(0, 0, 0)) {}
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
        void render(std::shared_ptr<VertexArray> vao, int mode);
    };
}