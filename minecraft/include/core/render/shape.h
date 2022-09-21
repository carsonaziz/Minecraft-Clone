#pragma once

#include <memory>

#include "core/render/vertex_array.h"

namespace Minecraft
{
    class Shape
    {
    protected:
        std::shared_ptr<VertexArray> m_vao;

    public:
        Shape() {}
        ~Shape() {}
        virtual std::shared_ptr<VertexArray>& get_vao() { return m_vao; }
    };
}