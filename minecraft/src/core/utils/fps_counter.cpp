#include "core/utils/fps_counter.h"

#include <chrono>

#include "core/log.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

namespace Minecraft
{
    FPSCounter::FPSCounter()
    {
        m_previous_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        m_current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    FPSCounter::~FPSCounter() {}

    int FPSCounter::tick()
    {
        static int frames;

        m_current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        m_nframes++;

        if (m_current_time - m_previous_time >= 1000.0)
        {
            frames = m_nframes;
            m_nframes = 0;
            m_previous_time += 1000.0;
        }

        return frames;
    }
}