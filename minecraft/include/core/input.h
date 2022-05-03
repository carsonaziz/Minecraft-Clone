#pragma once

namespace Minecraft
{
    namespace Input
    {
        bool is_key_down(int keycode);
        bool is_mouse_button_down(int button);
        
        float get_mouse_x();
        float get_mouse_y();
    };
}