#include "core/log.h"
#include "core/application.h"
#include "utils/texture_packer.h"

int main()
{
    Minecraft::Log::init();
    auto app = Minecraft::Application::create();
    Minecraft::TexturePacker::pack(32);
    app->run();

    delete app;
}
