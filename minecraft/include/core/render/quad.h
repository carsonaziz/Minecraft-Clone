#pragma once

#include <memory>

#include "vertex_array.h"

namespace Minecraft
{
    class Quad
    {
    private:
        std::shared_ptr<VertexArray> m_vao;

    public:
        Quad();
        ~Quad();

        inline std::shared_ptr<VertexArray>& get_vao() { return m_vao; }
    };
}