#pragma once

#include <memory>

#include "events/window_event.h"
#include "layers/layer_stack.h"
#include "window.h"

namespace Minecraft
{
    class Application
    {
    private:
        static Application* s_instance;

        std::shared_ptr<Window> m_window;
        std::unique_ptr<LayerStack> m_layer_stack;


        bool m_running;

    private:
        void on_event(Event& event);
        bool on_window_close(WindowCloseEvent& event);
        Application();
    public:
        ~Application() {}

        void run();

        inline std::shared_ptr<Window>& get_window() { return m_window; }

        inline static Application* get() { return s_instance; }
        static Application* create();
    };
}