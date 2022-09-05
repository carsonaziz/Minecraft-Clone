#pragma once

#include <string>
#include <cstdint>

namespace Minecraft
{
    namespace TextureUtil
    {
        void pack(int size);
        int get_img_block_height(const std::string path);
        void write_image(const std::string filename, int index);
        void generate_texture_format(const std::string name, int index_x, int index_y);
        
        unsigned char* load_image(const std::string& filepath, int* width, int* height, int* channels);
        unsigned char* load_image_from_int64(uint64_t source);
    }
}