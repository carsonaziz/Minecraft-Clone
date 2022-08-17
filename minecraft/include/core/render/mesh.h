#pragma once

#include <memory>

#include "vertex_array.h"
#include "core/log.h"

namespace Minecraft
{
    class Mesh
    {
    private:
        std::shared_ptr<VertexArray> m_vao;

    public:
        Mesh(std::shared_ptr<VertexArray> vao) : m_vao(vao) {}
        ~Mesh() {}

        inline std::shared_ptr<VertexArray>& get_vao() { return m_vao; }
    };
}