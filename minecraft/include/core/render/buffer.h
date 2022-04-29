#pragma once

namespace Minecraft
{
    struct BufferLayout
    {
        int Index;
        int Length;

        BufferLayout(int index, int length)
            : Index(index), Length(length) {}
    };

    class VertexBuffer
    {
    private:
        unsigned int m_vbo;
        BufferLayout m_layout;
        int m_vertex_count;
    public:
        VertexBuffer(float* data, int data_size, const BufferLayout& layout);
        ~VertexBuffer();

        void bind();
        void unbind();

        inline BufferLayout& get_layout() { return m_layout; }
        inline int get_vertex_count() { return m_vertex_count; }
    };
}