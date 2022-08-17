#pragma once

#include <vector>
#include <array>
#include <glm/glm.hpp>

#include "core/render/mesh.h"

namespace Minecraft
{
    // will be 64 bits (8 bytes)
    struct Block
    {
        uint16_t Id;
        // other stuff to be added (e.g. direction)

        Block(int id = 0) : Id(id) {}
    };

    class Chunk
    {
    public:
        static const int SIZEX = 16;
        static const int SIZEY = 255;
        static const int SIZEZ = 16;
    private:
        std::array<Block, SIZEX * SIZEY * SIZEZ> m_blocks;
        glm::vec3 m_position;

        std::shared_ptr<Mesh> m_mesh;

        bool m_changed;
    
    public:
        Chunk(const glm::vec3& position) : m_position(position) {}
        ~Chunk() {}

        Block& get_block(int x, int y, int z);
        void set_block(int x, int y, int z, int block_id);

        inline void set_mesh(std::shared_ptr<Mesh> mesh) { m_mesh = mesh; }
        inline std::shared_ptr<Mesh> get_mesh() const { return m_mesh; }

        inline void set_changed(bool value) { m_changed = value; }
        inline bool get_changed() const { return m_changed; }

        inline const glm::vec3& get_position() { return m_position; }
    };
}