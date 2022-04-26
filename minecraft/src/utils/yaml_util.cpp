#include "utils/yaml_util.h"

#include <yaml-cpp/yaml.h>
#include <fstream>

namespace Minecraft
{
    namespace YamlUtil
    {
        void write_texture_formats(std::vector<TextureFormat> formats)
        {
            YAML::Node texture_format;
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

                texture_format[format.name] = uvs;
            }

            std::ofstream fout("minecraft/res/texture_formats.yaml");
            fout << texture_format;
        }
    }
}