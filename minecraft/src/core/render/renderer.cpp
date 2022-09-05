#include "core/render/renderer.h"

#include <glad/glad.h>

#include "core/log.h"

namespace Minecraft
{
    namespace Render
    {
        // forward declare internal functions
        void draw_arrays(int vertex_count);

        RenderInfo* info = nullptr;

        void init()
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

            info = new RenderInfo();
        }

        RenderStats& get_stats()
        {
            return info->stats;
        }

        void toggle_render_mode()
        {
            switch (info->render_mode)
            {
            case GL_FILL:
                info->render_mode = GL_LINE;
                break;
            
            case GL_LINE:
                info->render_mode = GL_FILL;
                break;
            }
        }

        void clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // reset triangle count to 0
            info->stats.triangle_count = 0;
        }

        void render(std::shared_ptr<VertexArray> vao)
        {
            vao->bind();
            draw_arrays(vao->get_vertex_count());

            // number of triangles rendered
            info->stats.triangle_count += vao->get_vertex_count() / 3;
        }

        void draw_arrays(int vertex_count)
        {
            glPolygonMode(GL_FRONT_AND_BACK, info->render_mode);
            glDrawArrays(GL_TRIANGLES, 0, vertex_count);
        }
    }
}