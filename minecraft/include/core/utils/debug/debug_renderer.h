#pragma once

namespace Minecraft
{
    // forward declarations
    namespace Debug
    {
        struct DebugItem;
        struct DebugList;
    }

    namespace DebugRender
    {
        const int CHAR_WIDTH = 48;
        const int CHAR_HEIGHT = 48;
        
        void init();
        void render_debug_item(Debug::DebugItem& item);
        void render_debug_list(Debug::DebugList* list);
        void shutdown();
    }
}