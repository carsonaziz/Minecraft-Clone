#include "world_generation/chunk.h"

namespace Minecraft
{
    Chunk::Chunk(const glm::vec3& position) : m_position(position), m_changed(true)
    {
        m_blocks.resize(SIZEX * SIZEY * SIZEZ);
    }
    Chunk::~Chunk()
    {
    }

    Block& Chunk::get_block(int x, int y, int z)
    {
        return m_blocks[y * (SIZEZ * SIZEX) + z * SIZEX + x];
    }
}