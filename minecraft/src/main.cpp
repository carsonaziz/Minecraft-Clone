#include "log.h"
#include "application.h"

int main()
{
    Minecraft::Log::init();
    auto app = Minecraft::Application::create();
    app->run();
}