#include "core/render/line.h"

namespace Minecraft
{
    Line::Line(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color) : Shape(), m_color(color)
    {
        glm::tvec3<float> vertices[2] = 
        {
            start, end
        };

        m_vao = std::make_shared<VertexArray>(2);
        m_vao->bind();

        BufferLayout layout({0, 3, sizeof(glm::tvec3<float>)});
        VertexBuffer buffer(vertices, 2 * sizeof(glm::tvec3<float>), layout);
        m_vao->add_vertex_buffer(buffer, GL_FLOAT);

        m_vao->unbind();
    }
}