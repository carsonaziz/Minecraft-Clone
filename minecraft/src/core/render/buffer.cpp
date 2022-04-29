#include "core/render/buffer.h"

#include <glad/glad.h>

#include "core/log.h"

namespace Minecraft
{
    VertexBuffer::VertexBuffer(float* data, int data_size, const BufferLayout& layout)
        : m_vertex_count(data_size/sizeof(float)/layout.Length), m_layout({layout})
    {
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_vbo);
    }

    void VertexBuffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    }

    void VertexBuffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}