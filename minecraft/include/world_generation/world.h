#pragma once

#include <vector>
#include <unordered_map>

#include "chunk.h"
#include "core/render/vertex_array.h"

namespace Minecraft
{
    class World
    {
    private:
        int m_render_distance = 2;

        std::vector<Chunk*> m_chunks;

    public:
        World();
        ~World();

        void update();

        inline std::vector<Chunk*>& get_chunks() { return m_chunks; }
    };
}