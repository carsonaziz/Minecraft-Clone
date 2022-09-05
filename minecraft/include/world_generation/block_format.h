#pragma once

#include <string>

namespace Minecraft
{
    struct BlockFormat
    {
        int id;
        std::string name;
        std::string top;
        std::string bottom;
        std::string left;
        std::string right;
        std::string front;
        std::string back;
    };
}