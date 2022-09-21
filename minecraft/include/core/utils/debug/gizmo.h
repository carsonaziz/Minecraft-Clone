#pragma once

#include "core/camera/camera_controller.h"
#include "core/render/line.h"

namespace Minecraft
{
    class Gizmo
    {
    private:
        std::shared_ptr<Line> m_x_axis;
        std::shared_ptr<Line> m_y_axis;
        std::shared_ptr<Line> m_z_axis;
    
    public:
        Gizmo();
        ~Gizmo() {}

        inline const std::shared_ptr<Line>& get_x_axis() { return m_x_axis; }
        inline const std::shared_ptr<Line>& get_y_axis() { return m_y_axis; }
        inline const std::shared_ptr<Line>& get_z_axis() { return m_z_axis; }
    };
}