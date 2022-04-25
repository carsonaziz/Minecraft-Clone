#include "application.h"

#include "log.h"

namespace Minecraft
{
    std::unique_ptr<Application> Application::create()
    {
        return std::make_unique<Application>();
    }

    void Application::run()
    {
        MC_LOG_INFO("Application Running!");
    }
}