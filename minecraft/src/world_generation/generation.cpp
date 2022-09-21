#include "world_generation/generation.h"

#include "core/render/buffer.h"
#include "core/render/mesh.h"
#include "core/log.h"
#include "core/utils/yaml_util.h"

namespace Minecraft
{
    glm::ivec3 block_offsets[6] = 
    {
        glm::ivec3(0, 0, -1),
        glm::ivec3(0, 0, 1),
        glm::ivec3(-1, 0, 0),
        glm::ivec3(1, 0, 0),
        glm::ivec3(0, -1, 0),
        glm::ivec3(0, 1, 0),
    };

    // forward declare internal functions
    TextureFormat& get_texture_format(int i, const BlockFormat& format);
    void build_mesh(glm::tvec3<uint16_t>* positions, int pos_count, glm::tvec2<float>* uvs, int uv_count, Chunk* chunk);

    void Generation::init()
    {
        YamlUtil::read_texture_formats("minecraft/res/blockdata/texture_formats.yaml", texture_map);
        YamlUtil::read_block_formats("minecraft/res/blockdata/block_formats.yaml", block_map);
    }

    void Generation::generate_blocks(Chunk* chunk)
    {
        int index = 0;
        for (uint8_t y = 0; y < Chunk::SIZEY; y++)
        {
            for (uint8_t z = 0; z < Chunk::SIZEZ; z++)
            {
                for (uint8_t x = 0; x < Chunk::SIZEX; x++)
                {
                    glm::ivec3 pos = glm::ivec3(x, y, z);
                    if (y >= Chunk::SIZEY - 2)
                        chunk->set_block(pos, 0);
                    else if (y == Chunk::SIZEY - 3)
                        chunk->set_block(pos, 2);
                    else if (y == 1)
                        chunk->set_block(pos, 3);
                    else if (y == 0)
                        chunk->set_block(pos, 0);
                    else
                        chunk->set_block(pos, 1);
                }
            }
        }
    }

    void Generation::generate_mesh(Chunk* chunk, World& world)
    {
        //////////////////////////////////////////////////////////////////////////////////////////
        // Vertices -   5 bits x, 9 bits y, 5 bits z = 19 bits
        // Normals -    1 bit x, y, z (0 positive, 1 negative, magnitude is only ever 1) = 3 bits
        // Uvs -        (2 bits can be used to declare which corner the vertex is, and then 
        //               information about the texture will be sent to calculate the texture coords on the gpu)
        // TODO: Implement vertex compression as above
        //////////////////////////////////////////////////////////////////////////////////////////

        int max_vertex_count = Chunk::SIZEX * Chunk::SIZEY * Chunk::SIZEZ * 6 * 6;

        // create array for positions and initialize to 0
        glm::tvec3<uint16_t>* positions = new glm::tvec3<uint16_t>[max_vertex_count];
        for (int i = 0; i < max_vertex_count; i++) positions[i] = glm::tvec3<uint16_t>(0, 0, 0);

        // create array for uvs and initialize to 0
        glm::tvec2<float>* uvs = new glm::tvec2<float>[max_vertex_count]; 
        for (int i = 0; i < max_vertex_count; i++) uvs[i] = glm::tvec2<float>(0, 0);

        int pos_index = 0;
        int uv_index = 0;
        for (uint16_t y = 0; y < Chunk::SIZEY; y++)
        {
            for (uint16_t z = 0; z < Chunk::SIZEZ; z++)
            {
                for (uint16_t x = 0; x < Chunk::SIZEX; x++)
                {
                    glm::ivec3 block_position = glm::ivec3(x, y, z);
                    Block* block = chunk->get_block(block_position, world);

                    // block.Id 0 is air so it is not attempted to be drawn
                    if (block->Id == 0) continue;

                    // block format contains textures corresponding to face of block
                    BlockFormat block_format = block_map[block->Id];

                    int face = 0;
                    for (const glm::ivec3& offset : block_offsets)
                    {
                        Block* block_to_check = chunk->get_block(block_position + offset, world);
                        if (block_to_check == nullptr) 
                        {
                            face++;
                            continue;
                        }

                        if (block_to_check->Id == 0)
                        {
                            for (int i = 0; i < BlockData::VERTICES_PER_FACE; i++)
                            {
                                positions[pos_index++] =  BlockData::vertices[face][i] + block_position;
                            }

                            TextureFormat& face_uvs = get_texture_format(face, block_format);
                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv2;
                            uvs[uv_index++] = face_uvs.uv1;
                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv3;
                            uvs[uv_index++] = face_uvs.uv2;
                        }

                        face++;
                    }
                }
            }
        }

        build_mesh(positions, pos_index, uvs, uv_index, chunk);

        delete[] positions;
        delete[] uvs;
    }

    void build_mesh(glm::tvec3<uint16_t>* positions, int pos_count, glm::tvec2<float>* uvs, int uv_count, Chunk* chunk)
    {
        std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>(pos_count);
        vao->bind();

        // positions
        BufferLayout pos_layout(0, 3, sizeof(glm::tvec3<uint16_t>));
        VertexBuffer pos_buffer(positions,  pos_count * sizeof(glm::tvec3<uint16_t>), pos_layout);
        vao->add_vertex_buffer(pos_buffer, GL_SHORT);

        // uvs
        BufferLayout uv_layout(1, 2, sizeof(glm::tvec2<float>));
        VertexBuffer uv_buffer(uvs, uv_count * sizeof(glm::tvec2<float>), uv_layout);
        // vao.add_vertex_buffer(uv_buffer, GL_FLOAT);

        glVertexAttribPointer(uv_layout.Index, uv_layout.Length, GL_FLOAT, GL_FALSE, uv_layout.DataSize, nullptr);
        glEnableVertexAttribArray(1);

        vao->unbind();

        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vao);

        chunk->set_mesh(mesh);
    }

    TextureFormat& get_texture_format(int i, const BlockFormat& format)
    {
        std::string texture_name;

        switch (i)
        {
        case 0:
            texture_name = format.back;
            break;
        case 1:
            texture_name = format.front;
            break;
        case 2:
            texture_name = format.left;
            break;
        case 3:
            texture_name = format.right;
            break;
        case 4:
            texture_name = format.bottom;
            break;
        case 5:
            texture_name = format.top;
            break;
        }

        return Generation::texture_map[texture_name];
    }
}