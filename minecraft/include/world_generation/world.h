#pragma once

#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "core/render/vertex_array.h"

namespace Minecraft
{
    class Chunk;

    class World
    {
    private:
        int m_render_distance = 5;

        std::vector<Chunk*> m_chunks;
        std::unordered_map<glm::vec2, Chunk*> m_chunk_positions;

    public:
        World();
        ~World();

        void update();

        // inline std::vector<Chunk*>& get_chunks() { return m_chunks; }
        inline std::unordered_map<glm::vec2, Chunk*>& get_chunks() { return m_chunk_positions; }
        inline Chunk* get_chunk(const glm::vec2& pos) { return m_chunk_positions[pos]; }
    };
}