#pragma once

#include <glm/glm.hpp>
#include <iostream>

#include "chunk.h"
#include "core/render/vertex_array.h"

namespace Minecraft
{
    namespace Generation
    {
        // Will get much more complicated, will likely be multiple functions
        void generate_blocks(Chunk& chunk);

        const VertexArray generate_mesh(Chunk& chunk);
    }
}