#include "core/render/vertex_array.h"

#include <glad/glad.h>

#include "core/log.h"

namespace Minecraft
{
    VertexArray::VertexArray(int vertex_count) : m_vertex_count(vertex_count)
    {
        glGenVertexArrays(1, &m_vao);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_vao);
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(m_vao);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::add_vertex_buffer(const VertexBuffer& buffer, int type)
    {
        glBindVertexArray(m_vao);
        BufferLayout layout = buffer.get_layout();

        glVertexAttribPointer(layout.Index, layout.Length, type, GL_FALSE, layout.DataSize, nullptr);
        glEnableVertexAttribArray(0);

        m_buffers.push_back(buffer);
        glBindVertexArray(0);
    }
}