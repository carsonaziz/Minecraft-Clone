#include "world_generation/chunk.h"

#include "core/log.h"

namespace Minecraft
{
    Block& Chunk::get_block(int x, int y, int z)
    {
        return m_blocks[y * (SIZEZ * SIZEX) + z * SIZEX + x];
    }

    void Chunk::set_block(int x, int y, int z, int block_id)
    {
        m_blocks[y * (SIZEZ * SIZEX) + z * SIZEX + x].Id = block_id;
    }
}