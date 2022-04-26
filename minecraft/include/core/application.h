#pragma once
#include <memory>

#include "events/event.h"

namespace Minecraft
{
    class Application
    {
    public:
        Application() {}
        ~Application() {}

        static std::unique_ptr<Application> create();

        void run();

        bool test(Event& event);
    };
}