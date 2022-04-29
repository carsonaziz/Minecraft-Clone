#pragma once

#include <vector>
#include <memory>

#include "buffer.h"

namespace Minecraft
{
    class VertexArray
    {
    private:
        unsigned int m_vao;
        int m_vertex_count;
        std::vector<std::shared_ptr<VertexBuffer>> m_buffers;
    public:
        VertexArray();
        ~VertexArray();

        void bind();
        void unbind();

        inline int get_vertex_count() { return m_vertex_count; }
        void add_vertex_buffer(std::shared_ptr<VertexBuffer>& buffer);
    };
}