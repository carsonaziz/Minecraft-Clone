#include "core/application.h"

#include "core/log.h"
#include "core/events/key_event.h"

namespace Minecraft
{
    std::unique_ptr<Application> Application::create()
    {
        return std::make_unique<Application>();
        MC_LOG_INFO("Application created");
    }

    void Application::run()
    {
        KeyPressedEvent event(57, 1);
        EventHandler handler(event);
        handler.handle_event<KeyPressedEvent>(std::bind(&Application::test, this, std::placeholders::_1));
    }

    bool Application::test(Event& event)
    {   
        MC_LOG_WARN(event.to_string());
        return true;
    }
}