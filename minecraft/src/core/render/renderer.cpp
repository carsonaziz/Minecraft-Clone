#include "core/render/renderer.h"

#include <glad/glad.h>

#include "core/log.h"

namespace Minecraft
{
    Renderer::Renderer()
    {
        init();
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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}