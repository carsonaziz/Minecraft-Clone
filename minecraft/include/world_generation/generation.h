#pragma once

#include <glm/glm.hpp>

#include "chunk.h"
#include "core/render/vertex_array.h"
#include "block_format.h"
#include "core/utils/texture_format.h"

namespace Minecraft
{
    namespace Generation
    {
        // make object to store these and make a member of that object in world renderer
        static std::unordered_map<std::string, TextureFormat> texture_map;
        static std::unordered_map<int, BlockFormat> block_map;

        void init();

        // Will get much more complicated, will likely be multiple functions
        void generate_blocks(Chunk* chunk);

        void generate_mesh(Chunk* chunk, World& world);
    }
}