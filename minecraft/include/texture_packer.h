#include <string>

namespace Minecraft
{
    namespace TexturePacker
    {
        void pack(int size);
        int get_img_block_height(std::string path);
        void write_image(std::string path, int index);
    }
}