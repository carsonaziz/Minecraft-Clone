#pragma once

#include <vector>
#include <glm/glm.hpp>


namespace Minecraft
{
    // will be 64 bits (4 bytes)
    struct Block
    {
        uint16_t Id;
        // other stuff to be added

        Block(int id = 0) : Id(id) {}
    };

    struct Chunk
    {
    private:
        std::vector<Block> m_blocks;
        glm::vec3 m_position;
        bool m_changed;
    public:
        static const int SIZEX = 16;
        static const int SIZEY = 255;
        static const int SIZEZ = 16;
    
    public:
        Chunk(const glm::vec3& position);
        ~Chunk();

        Block& get_block(int x, int y, int z);

        inline const glm::vec3& get_position() { return m_position; }
        inline void set_changed(bool value) { m_changed = value; }
        inline bool get_changed() const { return m_changed; }
        inline std::vector<Block>& get_blocks() { return m_blocks; }
    };
}