#pragma once

#include <string>
#include <vector>

namespace Minecraft
{
    namespace Debug
    {   
        struct DebugItem
        {
            std::string text;
            int x;
            int y;
        };

        
        struct DebugList
        {
            std::vector<DebugItem> list;

            void push(const DebugItem& item)
            {
                list.insert(list.begin(), {item.text, item.x, item.y});
            }

            const DebugItem& peek_front()
            {
                return list.front();
            }

            void clear()
            {
                list.clear();
            }

            bool is_empty()
            {
                return list.size() == 0;
            }

            inline std::vector<DebugItem>::iterator begin() { return list.begin(); }
            inline std::vector<DebugItem>::iterator end() { return list.end(); }
        };

        void init();
        void text(std::string fmt, ...);
        void render();
        void shutdown();
    }
}