#include "core/application.h"

#include "core/log.h"
#include "core/layers/pause_menu_layer.h"
#include "core/layers/game_layer.h"

namespace Minecraft
{
    Application* Application::s_instance = nullptr;

    Application::Application() : m_running(true)
    {
        m_window = std::make_shared<Window>();
        m_layer_stack = std::make_unique<LayerStack>();
        m_renderer = std::make_shared<Renderer>();

        m_window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));
        m_pause_menu_layer = new PauseMenuLayer();
        m_game_layer = new GameLayer();

        m_layer_stack->push(m_pause_menu_layer);
        m_layer_stack->push(m_game_layer);
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
        while(m_running)
        {
            m_renderer->clear();

            for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
            {
                (*it)->update();
                (*it)->render(m_renderer);
            }

            m_window->swap_and_poll();
        }
    }
}