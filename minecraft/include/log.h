#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Minecraft
{
    class Log
    {
    private: 
        static std::shared_ptr<spdlog::logger>  s_console_log;
    public:
        static void init();
        static std::shared_ptr<spdlog::logger>& get() { return s_console_log; }
    };
}

// Logger macros
#define MC_LOG_TRACE(...) Minecraft::Log::get()->trace(__VA_ARGS__)
#define MC_LOG_INFO(...) Minecraft::Log::get()->info(__VA_ARGS__)
#define MC_LOG_WARN(...) Minecraft::Log::get()->warn(__VA_ARGS__)
#define MC_LOG_ERROR(...) Minecraft::Log::get()->error(__VA_ARGS__)