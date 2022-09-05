#include "core/application.h"

#include "core/log.h"
#include "core/layers/pause_menu_layer.h"
#include "core/layers/game_layer.h"
#include "core/layers/debug_layer.h"
#include "core/render/renderer.h"
#include "core/utils/fps_counter.h"

namespace Minecraft
{
    Application* Application::s_instance = nullptr;

    Application::Application() : m_running(true)
    {
        m_window = std::make_shared<Window>();
        m_layer_stack = std::make_unique<LayerStack>();

        m_window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));

        m_layer_stack->push(new PauseMenuLayer());
        m_layer_stack->push(new DebugLayer());
        m_layer_stack->push(new GameLayer());

        Render::init();
    }

    Application* Application::create()
    {
        if (s_instance == nullptr)
        {
            s_instance = new Application();
        }
        return s_instance;
    }

    void Application::on_event(Event& event)
    {
        EventHandler handler(event);
        handler.handle_event<WindowCloseEvent>(std::bind(&Application::on_window_close, this, std::placeholders::_1));

        for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
        {
            if (event.m_handled) break;
            (*it)->on_event(event);
        }
    }

    bool Application::on_window_close(WindowCloseEvent& event)
    {
        m_running = false;

        return true;
    }

    void Application::run()
    {
        double dt = 0;
        double previous_time = m_window->get_time();
        double current_time = m_window->get_time();

        FPSCounter fps_counter;

        while(m_running)
        {   
            dt = current_time - previous_time;
            previous_time = current_time;

            int frames = fps_counter.tick();
            Render::get_stats().frames = frames;
            Render::get_stats().ms_for_frame = 1.0f/(float)frames * 1000;

            for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
            {
                (*it)->update(dt);
            }

            Render::clear();

            for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
            {
                (*it)->render();
            }

            m_window->swap_and_poll();

            current_time = m_window->get_time();
        }
    }
}