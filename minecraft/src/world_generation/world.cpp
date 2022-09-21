#include "world_generation/world.h"

#include <glm/glm.hpp>

#include "world_generation/generation.h"
#include "world_generation/chunk.h"

namespace Minecraft
{
    World::World()
    {
        // Initialize generation with texture_map and block_map
        Generation::init();

        for (int z = 0; z < m_render_distance; z++)
        {
            for (int x = 0; x < m_render_distance; x++)
            {
                glm::vec2 position(x * Chunk::SIZEX, z * Chunk::SIZEZ);

                Chunk* chunk = new Chunk(position);
                Generation::generate_blocks(chunk);
                Generation::generate_mesh(chunk, *this);

                m_chunks.push_back(chunk);
                m_chunk_positions[position] = chunk;
            }
        }
    }

    World::~World() 
    {
        for (Chunk* chunk : m_chunks)
        {
            delete chunk;
        }
    }

    void World::update()
    {
        for (Chunk* chunk : m_chunks)
        {
            if (chunk->get_changed())
            {
                const glm::vec2& position = chunk->get_position();
                Generation::generate_mesh(chunk, *this);
                chunk->set_changed(false);
            }
        }
    }
}