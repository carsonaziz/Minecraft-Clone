#include "core/utils/yaml_util.h"

#include <yaml-cpp/yaml.h>
#include <fstream>

#include "core/log.h"

namespace Minecraft
{
    namespace YamlUtil
    {
        void write_texture_formats(std::vector<TextureFormat>& formats, const std::string& filepath)
        {
            YAML::Node texture_formats;
            for (auto& format : formats)
            {
                YAML::Node uvs;
                uvs["uv0"].push_back(format.uv0.x);
                uvs["uv0"].push_back(format.uv0.y);
                
                uvs["uv1"].push_back(format.uv1.x);
                uvs["uv1"].push_back(format.uv1.y);

                uvs["uv2"].push_back(format.uv2.x);
                uvs["uv2"].push_back(format.uv2.y);

                uvs["uv3"].push_back(format.uv3.x);
                uvs["uv3"].push_back(format.uv3.y);

                texture_formats[format.name] = uvs;
            }

            std::ofstream fout(filepath.c_str());
            fout << texture_formats;
        }

        void read_texture_formats(const std::string& filepath, std::unordered_map<std::string, TextureFormat>& formats)
        {
            YAML::Node texture_formats = YAML::LoadFile(filepath.c_str());

            for (const auto& texture : texture_formats)
            {
                std::string name = texture.first.as<std::string>();
                glm::vec2 uv0(texture.second["uv0"][0].as<float>(), texture.second["uv0"][1].as<float>());
                glm::vec2 uv1(texture.second["uv1"][0].as<float>(), texture.second["uv1"][1].as<float>());
                glm::vec2 uv2(texture.second["uv2"][0].as<float>(), texture.second["uv2"][1].as<float>());
                glm::vec2 uv3(texture.second["uv3"][0].as<float>(), texture.second["uv3"][1].as<float>());

                formats[name] = { name, uv0, uv1, uv2, uv3 };
            }
        }

        void read_block_formats(const std::string& filepath, std::unordered_map<int, BlockFormat>& formats)
        {
            YAML::Node block_formats = YAML::LoadFile(filepath.c_str());

            for (const auto& block : block_formats)
            {
                std::string name = block.first.as<std::string>();
                int id = block.second["id"].as<int>();
                std::string top = block.second["top"].as<std::string>();
                std::string bottom = block.second["bottom"].as<std::string>();
                std::string left = block.second["left"].as<std::string>();
                std::string right = block.second["right"].as<std::string>();
                std::string front = block.second["front"].as<std::string>();
                std::string back = block.second["back"].as<std::string>();

                formats[id] = { id, name, top, bottom, left, right, front, back };
            }
        }
    }
}