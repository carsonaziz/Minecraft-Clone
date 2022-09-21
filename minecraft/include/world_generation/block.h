#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Minecraft
{
    // will be 64 bits (8 bytes)
    struct Block
    {
        uint16_t Id;
        // other stuff to be added (e.g. direction)

        Block(int id = 0) : Id(id) {}
    };

    enum class BlockFace
    {
        Back    = 0,
        Front   = 1,
        Left    = 2,
        Right   = 3,
        Bottom  = 4,
        Top     = 5
    };

    namespace BlockData
    {
        constexpr int NUM_BLOCK_FACES = 6;
        constexpr int VERTICES_PER_FACE = 6;

        static glm::ivec3 vertices[6][6] = 
        {
            {
                // back face
                glm::ivec3(1, 0, 0),   glm::ivec3(0, 1, 0),   glm::ivec3(1, 1, 0),
                glm::ivec3(1, 0, 0),   glm::ivec3(0, 0, 0),   glm::ivec3(0, 1, 0)
            },
            {
                // front face
                glm::ivec3(0, 0, 1),   glm::ivec3(1, 1, 1),   glm::ivec3(0, 1, 1),
                glm::ivec3(0, 0, 1),   glm::ivec3(1, 0, 1),   glm::ivec3(1, 1, 1)
            },
            {
                // left face
                glm::ivec3(0, 0, 0),   glm::ivec3(0, 1, 1),   glm::ivec3(0, 1, 0),
                glm::ivec3(0, 0, 0),   glm::ivec3(0, 0, 1),   glm::ivec3(0, 1, 1)
            },
            {
                // right face
                glm::ivec3(1, 0, 1),   glm::ivec3(1, 1, 0),   glm::ivec3(1, 1, 1),
                glm::ivec3(1, 0, 1),   glm::ivec3(1, 0, 0),   glm::ivec3(1, 1, 0)
            },
            {
                // bottom face
                glm::ivec3(0, 0, 0),   glm::ivec3(1, 0, 1),   glm::ivec3(0, 0, 1),
                glm::ivec3(0, 0, 0),   glm::ivec3(1, 0, 0),   glm::ivec3(1, 0, 1)
            },
            {
                // top face
                glm::ivec3(0, 1, 1),   glm::ivec3(1, 1, 0),   glm::ivec3(0, 1, 0),
                glm::ivec3(0, 1, 1),   glm::ivec3(1, 1, 1),   glm::ivec3(1, 1, 0)
            }
        };
    }
}