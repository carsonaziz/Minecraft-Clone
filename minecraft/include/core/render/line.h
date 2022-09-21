#pragma once

#include <glm/glm.hpp>

#include "shape.h"

namespace Minecraft
{
    class Line : public Shape
    {
    private:
        glm::vec3 m_color;

    public:
        Line(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);
        ~Line() {}

        inline const glm::vec3& get_color() const { return m_color; }
    };
}