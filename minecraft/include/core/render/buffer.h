#pragma once

#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "core/log.h"

namespace Minecraft
{
    struct BufferLayout
    {
        int Index;
        int Length;
        size_t DataSize;

        BufferLayout() {}
        BufferLayout(int index, int length, size_t data_size)
            : Index(index), Length(length), DataSize(data_size) {}
    };

    class VertexBuffer
    {
    private:
        unsigned int m_vbo;
        BufferLayout m_layout;

    private:
        template <typename T>
        void init(T* data, int data_size);
    public:
        VertexBuffer(glm::tvec3<uint16_t>* data, int data_size, const BufferLayout& layout);
        VertexBuffer(glm::tvec2<float>* data, int data_size, const BufferLayout& layout);
        VertexBuffer(glm::tvec3<float>* data, int data_size, const BufferLayout& layout);
        ~VertexBuffer();

        void bind();
        void unbind();

        inline const BufferLayout& get_layout() const { return m_layout; }
    };
}