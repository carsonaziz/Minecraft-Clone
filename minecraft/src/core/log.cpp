#include "core/log.h"

namespace Minecraft
{
    std::shared_ptr<spdlog::logger> Log::s_console_log;
    void Log::init()
    {
        spdlog::set_pattern("%^[%T][%n]: %v%$");
        s_console_log = spdlog::stdout_color_mt("CONSOLE");
        s_console_log->set_level(spdlog::level::debug);
    }
}