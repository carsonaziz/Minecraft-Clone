#include "core/log.h"
#include "core/application.h"
#include "core/utils/texture_util.h"
#include "core/utils/yaml_util.h"

int main()
{
    Minecraft::Log::init();
    Minecraft::TextureUtil::pack(32);
    auto app = Minecraft::Application::create();
    app->run();

    delete app;
}
