#pragma once
#include <memory>

#include "events/event.h"
#include "layers/layer_stack.h"

namespace Minecraft
{
    class Application
    {
    private:
        std::unique_ptr<LayerStack> m_layer_stack;

        Layer* m_pause_menu_layer;
        Layer* m_game_layer;

    public:
        Application();
        ~Application() {} // determine whether layers should be deleted in application or layer_stack (probably application because it owns it)
        static std::unique_ptr<Application> create();

        void run();
    };
}