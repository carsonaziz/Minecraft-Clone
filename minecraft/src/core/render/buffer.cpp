#include "core/render/buffer.h"

#include "core/log.h"

namespace Minecraft
{
    VertexBuffer::VertexBuffer(glm::tvec3<uint16_t>* data, int data_size, const BufferLayout& layout) : m_layout(layout)
    {
        init(data, data_size);
    }

    VertexBuffer::VertexBuffer(glm::tvec2<float>* data, int data_size, const BufferLayout& layout) : m_layout(layout)
    {
        init(data, data_size);
    }

    VertexBuffer::VertexBuffer(glm::tvec3<float>* data, int data_size, const BufferLayout& layout) : m_layout(layout)
    {
        init(data, data_size);
    }

    template <typename T>
    void VertexBuffer::init(T* data, int data_size)
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