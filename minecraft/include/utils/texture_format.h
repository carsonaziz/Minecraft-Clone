#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Minecraft
{
    struct TextureFormat
    {
        std::string name;
        glm::vec2 uv0;
        glm::vec2 uv1;
        glm::vec2 uv2;
        glm::vec2 uv3;
    };
}