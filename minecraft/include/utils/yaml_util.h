#pragma once

#include <vector>

#include "texture_format.h"

namespace Minecraft
{
    namespace YamlUtil
    {
        void write_texture_formats(std::vector<TextureFormat> formats);
    }
}