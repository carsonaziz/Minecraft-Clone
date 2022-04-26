#include "core/application.h"

#include "core/log.h"

namespace Minecraft
{
    std::unique_ptr<Application> Application::create()
    {
        return std::make_unique<Application>();
        MC_LOG_INFO("Application created");
    }

    void Application::run()
    {

    }
}