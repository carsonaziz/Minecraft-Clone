#pragma once

#include <glm/glm.hpp>

#include "chunk.h"
#include "core/render/vertex_array.h"
#include "format.h"

namespace Minecraft
{
    namespace Generation
    {
        static std::unordered_map<std::string, TextureFormat> texture_map;
        static std::unordered_map<int, BlockFormat> block_map;

        void init();

        // Will get much more complicated, will likely be multiple functions
        void generate_blocks(Chunk* chunk);

        void generate_mesh(Chunk* chunk);
    }
}