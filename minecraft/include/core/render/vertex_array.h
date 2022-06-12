#pragma once

#include <vector>

#include "buffer.h"

namespace Minecraft
{
    class VertexArray
    {
    private:
        unsigned int m_vao;
        int m_vertex_count;
        std::vector<VertexBuffer> m_buffers;
    public:
        VertexArray(int vertex_count);
        ~VertexArray();

        void bind() const;
        void unbind() const;

        void add_vertex_buffer(const VertexBuffer& buffer, int type);

        inline int get_vertex_count() const { return m_vertex_count; }
    };
}