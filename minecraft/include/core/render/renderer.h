#pragma once

#include "vertex_array.h"
#include "world_generation/chunk.h"

namespace Minecraft
{
    namespace Render
    {
        void init();
        void clear();
        void render(std::shared_ptr<VertexArray> vao);
    };
}