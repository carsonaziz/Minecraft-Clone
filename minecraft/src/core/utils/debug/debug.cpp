#include "core/utils/debug/debug.h"

#include <cstdarg>

#include "core/log.h"
#include "core/utils/debug/debug_renderer.h"

namespace Minecraft
{
    namespace Debug
    {
        DebugList* debug_list = nullptr;

        void init()
        {
            debug_list = new DebugList();
        }

        void text(std::string fmt, ...)
        {
            va_list args;
            int len = 0;
            char* buffer;

            // load formatted string into buffer
            va_start(args, fmt);
            len = vsnprintf(NULL, 0, fmt.c_str(), args) + 1;
            buffer = new char[len];
            vsnprintf(buffer, len, fmt.c_str(), args);
            va_end(args);
            
            if (debug_list->is_empty())
            {
                debug_list->push({std::string(buffer), 0, 696});
            }
            else
            {
                debug_list->push({std::string(buffer), debug_list->peek_front().x, debug_list->peek_front().y - DebugRender::CHAR_HEIGHT / 2});
            }

            delete buffer;
        }

        void render()
        {
            DebugRender::render_debug_list(debug_list);
            debug_list->clear();
        }

        void shutdown()
        {
            delete debug_list;
        }
    }
}