#include "core/utils/texture_util.h"

#include <filesystem>
#include <vector>
#include <glm/glm.hpp>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "core/log.h"
#include "core/utils/yaml_util.h"
#include "world_generation/format.h"


namespace Minecraft
{
    namespace TextureUtil
    {   
        std::string base_path = "resourcepacks/Faithful/assets/minecraft/textures/block";
        int img_count = 0;
        int packed_channels = 4;    // only PNG is supported
        int packed_width = 0;
        int packed_height = 0;
        int atlas_offset = 0;       // if textures are stacked in one image this offset will allow them to be placed in the atlas without overwriting other textures
        unsigned char* packed_texture;

        std::vector<TextureFormat> texture_formats;

        void pack(int size)
        {
            // Count # of images in res
            for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(base_path.c_str()))
            {
                // Check if file is PNG
                if (strcmp(dirEntry.path().extension().c_str(), ".png") == 0)
                {
                    std::string file_path = base_path + "/" + dirEntry.path().filename().c_str();

                    img_count += get_img_block_height(file_path);
                }
            }
            
            packed_width = ceil(sqrt(img_count));
            packed_height = ceil(sqrt(img_count));
            
            // width (in blocks) * height (int blocks) * channels
            packed_texture = new unsigned char[(packed_width * size) * (packed_height * size) * packed_channels];

            // write to packed_texture
            int index = 0;
            for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(base_path.c_str()))
            {
                // Check if file is PNG
                if (strcmp(dirEntry.path().extension().c_str(), ".png") == 0)
                {
                    write_image(dirEntry.path().stem().c_str(), index);

                    index++;
                }
            }

            stbi_write_png("minecraft/res/texture_atlas.png", packed_width * size, packed_height * size, packed_channels, packed_texture, packed_width * size * packed_channels);
            delete[] packed_texture;

            YamlUtil::write_texture_formats(texture_formats, "minecraft/res/blockdata/texture_formats.yaml");
        }

        int get_img_block_height(const std::string path)
        {
            int width, height, channels;
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
            if(data == NULL) {
                MC_LOG_ERROR("Error in loading image");
                exit(1);
            }

            stbi_image_free(data);

            int block_height = height / width;

            if (width != 32)
            {
                block_height = 0;
            }
            return block_height;
        }

        void write_image(const std::string filename, int index)
        {
            int width, height, channels;
            std::string path = base_path + "/" + filename + ".png";
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
            if(data == NULL) {
                MC_LOG_ERROR("Error in loading image");
                exit(1);
            }

            if (width != 32) return;

            int tex_count = height / width;    // number of textures in images with stacked textures

            for (int i = 0; i < tex_count; i++)
            {
                MC_LOG_INFO("Packing textures {}%", (float)(index + atlas_offset) / (float)(img_count + 1) * 100);
                int index_x = (index + atlas_offset) % packed_width;
                int index_y = floor((index + atlas_offset) / packed_width);

                generate_texture_format(filename, index_x, index_y);
                for (int y = 0; y < width; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        int atlas_y = (index_y * packed_width * width * width * packed_channels);
                        int pixel_y = (y * packed_width * width * packed_channels);
                        int atlas_x = (index_x * width * packed_channels);
                        int pixel_x = (x * packed_channels);
                        int atlas_idx = pixel_x + atlas_x + pixel_y + atlas_y;
                            
                        packed_texture[atlas_idx + 0] = data[(x * channels) + (y * width * channels) + (i * width * width * channels) + 0];
                        packed_texture[atlas_idx + 1] = data[(x * channels) + (y * width * channels) + (i * width * width * channels) + 1];
                        packed_texture[atlas_idx + 2] = data[(x * channels) + (y * width * channels) + (i * width * width * channels) + 2];
                        if (channels == 4)
                        {
                            packed_texture[atlas_idx + 3] = data[(x * channels) + (y * width * channels) + (i * width * width * channels) + 3];
                        }
                        else if (channels == 3)
                        {
                            packed_texture[atlas_idx + 3] = 255;
                        }
                    }
                }
                if (tex_count > 1 && i != (tex_count-1)) atlas_offset++;  // only increase offset for stacked texture images, and dont increase for last one (done automatically by image index)
            }

            stbi_image_free(data);
        }

        void generate_texture_format(const std::string name, int index_x, int index_y)
        {
            TextureFormat format;
            format.name = name;
            format.uv0 = glm::vec2((float)index_x / (float)packed_width, 1 - (float)index_y / (float)packed_height - 1.0f / (float)packed_height);
            format.uv1 = glm::vec2((float)index_x / (float)packed_width, 1 - (float)index_y / (float)packed_height);
            format.uv2 = glm::vec2((float)index_x / (float)packed_width + 1.0f / (float)packed_width, 1 - (float)index_y / (float)packed_height);
            format.uv3 = glm::vec2((float)index_x / (float)packed_width + 1.0f / (float)packed_width, 1 - (float)index_y / (float)packed_height - 1.0f / (float)packed_height);

            texture_formats.push_back(format);
        }

        unsigned char* load_image(const std::string& filepath, int* width, int* height, int* channels)
        {
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(filepath.c_str(), width, height, channels, 0);

            if (data == NULL)
            {
                MC_LOG_ERROR("Error in loading image");
                exit(1);
            }

            return data;
        }
    }
}