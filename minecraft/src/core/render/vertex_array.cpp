#include "core/render/vertex_array.h"

#include <glad/glad.h>

#include "core/log.h"

namespace Minecraft
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_vao);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_vao);
    }

    void VertexArray::bind()
    {
        glBindVertexArray(m_vao);
    }

    void VertexArray::unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::add_vertex_buffer(std::shared_ptr<VertexBuffer>& buffer)
    {
        glBindVertexArray(m_vao);
        buffer->bind();
        BufferLayout layout = buffer->get_layout();

        glVertexAttribPointer(layout.Index, layout.Length, GL_FLOAT, GL_FALSE, sizeof(float) * layout.Length, nullptr);
        glEnableVertexAttribArray(0);

        if (m_buffers.empty())
            m_vertex_count = buffer->get_vertex_count();
        else if (m_vertex_count != buffer->get_vertex_count())
            MC_LOG_ERROR("Vertex count does not match");

        m_buffers.push_back(buffer);
        glBindVertexArray(0);
    }
}