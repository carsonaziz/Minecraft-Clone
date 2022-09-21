#pragma once

#include <vector>
#include <array>
#include <glm/glm.hpp>

#include "core/render/mesh.h"
#include "world_generation/block.h"

namespace Minecraft
{
    class World;

    class Chunk
    {
    public:
        static constexpr int SIZEX = 16;
        static constexpr int SIZEY = 255;
        static constexpr int SIZEZ = 16;
    private:
        std::array<Block, SIZEX * SIZEY * SIZEZ> m_blocks;
        glm::vec2 m_position;

        std::shared_ptr<Mesh> m_mesh;

        bool m_changed;
    
    public:
        Chunk(const glm::vec2& position) : m_position(position), m_changed(true) {}
        ~Chunk() {}

        Block* get_block(const glm::vec3& pos, World& world);
        void set_block(const glm::vec3& pos, int block_id);

        inline void set_mesh(std::shared_ptr<Mesh> mesh) { m_mesh = mesh; }
        inline std::shared_ptr<Mesh> get_mesh() const { return m_mesh; }

        inline void set_changed(bool value) { m_changed = value; }
        inline bool get_changed() const { return m_changed; }

        inline const glm::vec2& get_position() { return m_position; }
    };
}