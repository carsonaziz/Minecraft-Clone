#include "world_generation/world.h"

#include <glm/glm.hpp>

#include "world_generation/generation.h"

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
                Chunk* chunk = new Chunk(glm::vec3(x * 16, 0, z * 16));
                Generation::generate_blocks(chunk);
                Generation::generate_mesh(chunk);
                m_chunks.push_back(chunk);
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
                Generation::generate_mesh(chunk);
                chunk->set_changed(false);
            }
        }
    }
}