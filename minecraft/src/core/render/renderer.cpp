#include "core/render/renderer.h"

#include <glad/glad.h>

#include "core/log.h"

namespace Minecraft
{
    namespace Render
    {
        void init()
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
        }

        void clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void render(std::shared_ptr<VertexArray> vao)
        {
            vao->bind();
            glDrawArrays(GL_TRIANGLES, 0, vao->get_vertex_count());
        }
    }
}