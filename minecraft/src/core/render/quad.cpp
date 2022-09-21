#include "core/render/quad.h"

#include "core/render/buffer.h"

namespace Minecraft
{
    glm::tvec3<float> vertices[6]
    {
        glm::tvec3<float>(0.0f, 0.0f, -1.0f),
        glm::tvec3<float>(1.0f, 1.0f, -1.0f),
        glm::tvec3<float>(0.0f, 1.0f, -1.0f),

        glm::tvec3<float>(0.0f, 0.0f, -1.0f),
        glm::tvec3<float>(1.0f, 0.0f, -1.0f),
        glm::tvec3<float>(1.0f, 1.0f, -1.0f)
    };

    glm::tvec2<float> uvs[6]
    {
        glm::tvec2<float>(0, 0),
        glm::tvec2<float>(1, 1),
        glm::tvec2<float>(0, 1),
        glm::tvec2<float>(0, 0),
        glm::tvec2<float>(1, 0),
        glm::tvec2<float>(1, 1)
    };

    Quad::Quad() : Shape()
    {
        m_vao = std::make_shared<VertexArray>(6);
        m_vao->bind();

        BufferLayout layout({0, 3, sizeof(glm::tvec3<float>)});
        VertexBuffer buffer(vertices, 6 * sizeof(glm::tvec3<float>), layout);
        m_vao->add_vertex_buffer(buffer, GL_FLOAT);


        BufferLayout uv_layout(1, 2, sizeof(glm::tvec2<float>));
        VertexBuffer uv_buffer(uvs, 6 * sizeof(glm::tvec2<float>), uv_layout);

        glVertexAttribPointer(uv_layout.Index, uv_layout.Length, GL_FLOAT, GL_FALSE, uv_layout.DataSize, nullptr);
        glEnableVertexAttribArray(1);

        m_vao->unbind();
    }

    Quad::~Quad()
    {
    }
}