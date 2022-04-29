#pragma once

#include <memory>

#include "events/window_event.h"
#include "layers/layer_stack.h"
#include "window.h"
#include "render/renderer.h"

namespace Minecraft
{
    class Application
    {
    private:
        std::unique_ptr<Window> m_window;
        std::shared_ptr<Renderer> m_renderer;
        std::unique_ptr<LayerStack> m_layer_stack;

        Layer* m_pause_menu_layer;
        Layer* m_game_layer;

        bool m_running;

    private:
        void on_event(Event& event);
        bool on_window_close(WindowCloseEvent& event);
    public:
        Application();
        ~Application() {} // determine whether layers should be deleted in application or layer_stack (probably application because it owns it)
        static std::unique_ptr<Application> create();

        void run();
    };
}