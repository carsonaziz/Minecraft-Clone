#pragma once

#include <chrono>

#include "core/log.h"

namespace Minecraft
{
    struct Timer
    {
        std::chrono::time_point<std::chrono::steady_clock> start, end;
        std::chrono::duration<float> duration;

        Timer()
        {
            start = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;

            MC_LOG_WARN("{}ms", duration.count() * 1000.0f);
        }
    };
}