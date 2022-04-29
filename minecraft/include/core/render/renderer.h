#pragma once

#include "vertex_array.h"

namespace Minecraft
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void init();
        void clear();
        void render(VertexArray& vao);
    };
}