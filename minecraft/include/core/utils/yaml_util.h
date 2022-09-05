#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "texture_format.h"
#include "world_generation/block_format.h"

namespace Minecraft
{
    namespace YamlUtil
    {
        void write_texture_formats(std::vector<TextureFormat>& formats, const std::string& filepath);
        void read_texture_formats(const std::string& filepath, std::unordered_map<std::string, TextureFormat>& formats);
        void read_block_formats(const std::string& filepath, std::unordered_map<int, BlockFormat>& formats);
    }
}