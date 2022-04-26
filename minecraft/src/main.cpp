#include "core/log.h"
#include "core/application.h"
#include "texture_packer.h"

int main()
{
    Minecraft::Log::init();
    auto app = Minecraft::Application::create();
    Minecraft::TexturePacker::pack(32);
    app->run();
}