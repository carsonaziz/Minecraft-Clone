#include "world_generation/generation.h"

#include "core/render/buffer.h"
#include "core/log.h"

namespace Minecraft
{
    namespace Generation
    {
        void generate_blocks(Chunk& chunk)
        {
            int index = 0;
            for (uint8_t y = 0; y < Chunk::SIZEY; y++)
            {
                for (uint8_t z = 0; z < Chunk::SIZEZ; z++)
                {
                    for (uint8_t x = 0; x < Chunk::SIZEX; x++)
                    {
                        chunk.get_blocks()[index++] = 1;

                    }
                }
            }
        }

        const VertexArray generate_mesh(Chunk& chunk)
        {
            int max_vertex_count = Chunk::SIZEX * Chunk::SIZEY * Chunk::SIZEZ * 6 * 6;
            glm::vec3 chunk_position = chunk.get_position();

            // create array for vertices and initialize to 0
            glm::tvec3<uint16_t>* positions = new glm::tvec3<uint16_t>[max_vertex_count];
            for (int i = 0; i < max_vertex_count; i++) positions[i] = glm::tvec3<uint16_t>(0, 0, 0);

            int index = 0;
            for (uint16_t y = 0; y < Chunk::SIZEY; y++)
            {
                for (uint16_t z = 0; z < Chunk::SIZEZ; z++)
                {
                    for (uint16_t x = 0; x < Chunk::SIZEX; x++)
                    {
                        // if blocks have an id other than 0 (air = 0, will be more clear later) draw it
                        if (chunk.get_block(x, y, z).Id != 0)
                        {
                            // front face
                            if ((z < (Chunk::SIZEZ - 1) && chunk.get_block(x, y, z + 1).Id == 0) || z == (Chunk::SIZEZ - 1))
                            {
                                positions[index++] = glm::tvec3<uint16_t>(x, y, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x, y, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z + 1);
                                
                            }

                            // back face
                            if ((z > 0 && chunk.get_block(x, y, z - 1).Id == 0) || z == 0)
                            {
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y, z);
                                positions[index++] = glm::tvec3<uint16_t>(x, y + 1, z);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y, z);
                                positions[index++] = glm::tvec3<uint16_t>(x, y, z);
                                positions[index++] = glm::tvec3<uint16_t>(x, y + 1, z);
                            }

                            // right face
                            if ((x < (Chunk::SIZEX - 1) && chunk.get_block(x + 1, y, z).Id == 0) || x == (Chunk::SIZEX - 1))
                            {
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y, z);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);
                            }

                            // left face
                            if ((x > 0 && chunk.get_block(x - 1, y, z).Id == 0) || x == 0)
                            {
                                positions[index++] = glm::tvec3<uint16_t>(x, y, z);
                                positions[index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x, y + 1, z);
                                positions[index++] = glm::tvec3<uint16_t>(x, y, z);
                                positions[index++] = glm::tvec3<uint16_t>(x, y, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);
                            }

                            // top face
                            if ((y < (Chunk::SIZEY - 1) && chunk.get_block(x, y + 1, z).Id == 0) || y == (Chunk::SIZEY - 1))
                            {
                                positions[index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);
                                positions[index++] = glm::tvec3<uint16_t>(x, y + 1, z);
                                positions[index++] = glm::tvec3<uint16_t>(x, y + 1, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y + 1, z);
                            }

                            // bottom face
                            if ((y > 0 && chunk.get_block(x, y - 1, z).Id == 0) || y == 0)
                            {
                                positions[index++] = glm::tvec3<uint16_t>(x, y, z);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x, y, z + 1);
                                positions[index++] = glm::tvec3<uint16_t>(x, y, z);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y, z);
                                positions[index++] = glm::tvec3<uint16_t>(x + 1, y, z + 1);
                            }
                        }
                    }
                }
            }

            VertexArray vao(max_vertex_count);
            BufferLayout layout(0, 3, sizeof(glm::tvec3<uint16_t>));
            VertexBuffer buffer(positions,  max_vertex_count * sizeof(glm::tvec3<uint16_t>), layout);
            vao.add_vertex_buffer(buffer, GL_SHORT);

            delete[] positions;

            return vao;
        }
    }
}