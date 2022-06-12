#include "core/render/renderer.h"

#include <glad/glad.h>

#include "core/log.h"

namespace Minecraft
{
    Renderer::Renderer()
    {
        init();
        glEnable(GL_CULL_FACE);
        // glCullFace(GL_CW);
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::render(VertexArray& vao)
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, vao.get_vertex_count());
    }

    void Renderer::init()
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}