#include "world_generation/chunk.h"

#include "core/log.h"
#include "world_generation/chunk.h"
#include "world_generation/world.h"

namespace Minecraft
{
    Block* Chunk::get_block(const glm::vec3& pos, World& world)
    {
        glm::vec3 chunk_offset(0, 0, 0);

        if (pos.x < 0) chunk_offset = glm::vec3(-SIZEX, 0, 0);
        else if (pos.x >= SIZEX) chunk_offset = glm::vec3(SIZEX, 0, 0);
        else if (pos.y < 0) chunk_offset = glm::vec3(0, -SIZEY, 0);
        else if (pos.y >= SIZEY) chunk_offset = glm::vec3(0, SIZEY, 0);
        else if (pos.z < 0) chunk_offset = glm::vec3(0, 0, -SIZEZ);
        else if (pos.z >= SIZEZ) chunk_offset = glm::vec3(0, 0, SIZEZ);

        // if offset is (0, 0, 0) the block resides within the chunk that called this function
        if (chunk_offset != glm::vec3(0, 0, 0))
        {
            glm::vec2 chunk_pos = m_position + glm::vec2(chunk_offset.x, chunk_offset.z);
            if (world.get_chunks().find(chunk_pos) != world.get_chunks().end())
            {
                Chunk* chunk = world.get_chunks()[chunk_pos];
                glm::vec3 block_pos = glm::vec3(((int)pos.x + SIZEX) % SIZEX, pos.y, ((int)pos.z + SIZEZ) % SIZEZ);
                return chunk->get_block(block_pos, world);
            }
            return nullptr;
        }
        return &m_blocks[pos.y * (SIZEZ * SIZEX) + pos.z * SIZEX + pos.x];
    }

    void Chunk::set_block(const glm::vec3& pos, int block_id)
    {
        m_blocks[pos.y * (SIZEZ * SIZEX) + pos.z * SIZEX + pos.x].Id = block_id;
    }
}