#pragma once

#include <glm/glm.hpp>

namespace Minecraft
{
    namespace Input
    {
        bool is_key_down(int keycode);
        bool is_mouse_button_down(int button);
        
        float get_mouse_x();
        float get_mouse_y();
        void toggle_cursor();
        const glm::vec2 get_mouse_pos();
    };
}