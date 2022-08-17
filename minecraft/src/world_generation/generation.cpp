#include "world_generation/generation.h"

#include "core/render/buffer.h"
#include "core/render/mesh.h"
#include "core/log.h"
#include "core/utils/yaml_util.h"

namespace Minecraft
{
    namespace Generation
    {
        void init()
        {
            YamlUtil::read_texture_formats("minecraft/res/blockdata/texture_formats.yaml", texture_map);
            YamlUtil::read_block_formats("minecraft/res/blockdata/block_formats.yaml", block_map);
        }

        void generate_blocks(Chunk* chunk)
        {
            int index = 0;
            for (uint8_t y = 0; y < Chunk::SIZEY; y++)
            {
                for (uint8_t z = 0; z < Chunk::SIZEZ; z++)
                {
                    for (uint8_t x = 0; x < Chunk::SIZEX; x++)
                    {
                        if (y == Chunk::SIZEY - 1)
                            chunk->set_block(x, y, z, 2);
                        else if (y == 0)
                            chunk->set_block(x, y, z, 3);
                        else
                            chunk->set_block(x, y, z, 1);
                    }
                }
            }
        }

        void generate_mesh(Chunk* chunk)
        {
            int max_vertex_count = Chunk::SIZEX * Chunk::SIZEY * Chunk::SIZEZ * 6 * 6;

            // create array for positions and initialize to 0
            glm::tvec3<uint16_t>* positions = new glm::tvec3<uint16_t>[max_vertex_count];
            for (int i = 0; i < max_vertex_count; i++) positions[i] = glm::tvec3<uint16_t>(0, 0, 0);

            // create array for uvs and initialize to 0
            glm::tvec2<float>* uvs = new glm::tvec2<float>[max_vertex_count]; 
            for (int i = 0; i < max_vertex_count; i++) uvs[i] = glm::tvec2<float>(0, 0);

            // Vertices -   5 bits x, 9 bits y, 5 bits z = 19 bits
            // Normals -    1 bit x, y, z (0 positive, 1 negative, value is only ever 1) = 3 bits
            // Uvs -        4 bytes u, v = 8 bytes

            // Total = 10 bytes = 16 bytes
            // Figure out how to not use 16 bytes (maybe reduce uvs somehow)

            // generate vertex data for chunk
            int pos_index = 0;
            int uv_index = 0;
            for (uint16_t y = 0; y < Chunk::SIZEY; y++)
            {
                for (uint16_t z = 0; z < Chunk::SIZEZ; z++)
                {
                    for (uint16_t x = 0; x < Chunk::SIZEX; x++)
                    {
                        // if blocks have an id other than 0 (air = 0, will be more clear later) draw it
                        int block_id = chunk->get_block(x, y, z).Id;

                        if (block_id == 0) continue;

                        // get block face uvs
                        BlockFormat block_format = block_map[block_id];

                        // front face
                        if ((z < (Chunk::SIZEZ - 1) && chunk->get_block(x, y, z + 1).Id == 0) || z == (Chunk::SIZEZ - 1))
                        {
                            // positions
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z + 1);

                            // uvs
                            TextureFormat face_uvs = texture_map[block_format.front];

                            // uvs[uv_index++] = glm::tvec2<float>(0, 0);
                            // uvs[uv_index++] = glm::tvec2<float>(1, 1);
                            // uvs[uv_index++] = glm::tvec2<float>(0, 1);
                            // uvs[uv_index++] = glm::tvec2<float>(0, 0);
                            // uvs[uv_index++] = glm::tvec2<float>(1, 0);
                            // uvs[uv_index++] = glm::tvec2<float>(1, 1);

                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv2;
                            uvs[uv_index++] = face_uvs.uv1;
                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv3;
                            uvs[uv_index++] = face_uvs.uv2;
                        }

                        // back face
                        if ((z > 0 && chunk->get_block(x, y, z - 1).Id == 0) || z == 0)
                        {
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y + 1, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y + 1, z);

                            // uvs
                            TextureFormat face_uvs = texture_map[block_format.back];

                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv2;
                            uvs[uv_index++] = face_uvs.uv1;
                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv3;
                            uvs[uv_index++] = face_uvs.uv2;
                        }

                        // right face
                        if ((x < (Chunk::SIZEX - 1) && chunk->get_block(x + 1, y, z).Id == 0) || x == (Chunk::SIZEX - 1))
                        {
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);

                            // uvs
                            TextureFormat face_uvs = texture_map[block_format.right];

                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv2;
                            uvs[uv_index++] = face_uvs.uv1;
                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv3;
                            uvs[uv_index++] = face_uvs.uv2;
                        }

                        // left face
                        if ((x > 0 && chunk->get_block(x - 1, y, z).Id == 0) || x == 0)
                        {
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y + 1, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);

                            // uvs
                            TextureFormat face_uvs = texture_map[block_format.left];

                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv2;
                            uvs[uv_index++] = face_uvs.uv1;
                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv3;
                            uvs[uv_index++] = face_uvs.uv2;
                        }

                        // top face
                        if ((y < (Chunk::SIZEY - 1) && chunk->get_block(x, y + 1, z).Id == 0) || y == (Chunk::SIZEY - 1))
                        {
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y + 1, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);

                            // uvs
                            TextureFormat face_uvs = texture_map[block_format.top];

                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv2;
                            uvs[uv_index++] = face_uvs.uv1;
                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv3;
                            uvs[uv_index++] = face_uvs.uv2;
                        }

                        // bottom face
                        if ((y > 0 && chunk->get_block(x, y - 1, z).Id == 0) || y == 0)
                        {
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y, z + 1);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x, y, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y, z);
                            positions[pos_index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);

                            // uvs
                            TextureFormat face_uvs = texture_map[block_format.bottom];

                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv2;
                            uvs[uv_index++] = face_uvs.uv1;
                            uvs[uv_index++] = face_uvs.uv0;
                            uvs[uv_index++] = face_uvs.uv3;
                            uvs[uv_index++] = face_uvs.uv2;
                        }
                        
                    }
                }
            }

            //TODO::Seperate into seperate function
            std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>(pos_index);    // pos_index is number of vertices in mesh
            vao->bind();

            // positions
            BufferLayout pos_layout(0, 3, sizeof(glm::tvec3<uint16_t>));
            VertexBuffer pos_buffer(positions,  pos_index * sizeof(glm::tvec3<uint16_t>), pos_layout);
            vao->add_vertex_buffer(pos_buffer, GL_SHORT);

            // uvs
            BufferLayout uv_layout(1, 2, sizeof(glm::tvec2<float>));
            VertexBuffer uv_buffer(uvs, uv_index * sizeof(glm::tvec2<float>), uv_layout);
            // vao.add_vertex_buffer(uv_buffer, GL_FLOAT);

            glVertexAttribPointer(uv_layout.Index, uv_layout.Length, GL_FLOAT, GL_FALSE, uv_layout.DataSize, nullptr);
            glEnableVertexAttribArray(1);

            vao->unbind();

            std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vao);

            delete[] positions;
            delete[] uvs;

            chunk->set_mesh(mesh);
        }
    }
}