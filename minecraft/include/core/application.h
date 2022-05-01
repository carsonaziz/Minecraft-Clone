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
        static Application* s_instance;

        std::shared_ptr<Window> m_window;
        std::unique_ptr<LayerStack> m_layer_stack;
        std::shared_ptr<Renderer> m_renderer;

        Layer* m_pause_menu_layer;
        Layer* m_game_layer;

        bool m_running;

    private:
        void on_event(Event& event);
        bool on_window_close(WindowCloseEvent& event);
        Application();
    public:
        ~Application() {} // determine whether layers should be deleted in application or layer_stack (probably application because it owns it)

        void run();

        inline std::shared_ptr<Window>& get_window() { return m_window; }

        inline static Application* get() { return s_instance; }
        static Application* create();
    };
}