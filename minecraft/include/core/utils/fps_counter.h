#pragma once

namespace Minecraft
{
    class FPSCounter
    {
    private:
        long m_current_time;
        long m_previous_time;
        int m_nframes;

    public:
        FPSCounter();
        ~FPSCounter();

        int tick();
    };
}