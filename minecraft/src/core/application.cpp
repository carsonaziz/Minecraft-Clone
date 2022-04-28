#include "core/application.h"

#include "core/log.h"
#include "core/events/key_event.h"
#include "core/layers/pause_menu_layer.h"
#include "core/layers/game_layer.h"

namespace Minecraft
{
    Application::Application()
    {
        m_layer_stack = std::make_unique<LayerStack>();
        m_pause_menu_layer = new PauseMenuLayer();
        m_game_layer = new GameLayer();
        m_layer_stack->push(m_game_layer);
        m_layer_stack->push(m_pause_menu_layer);
    }

    std::unique_ptr<Application> Application::create()
    {
        return std::make_unique<Application>();
        MC_LOG_INFO("Application created");
    }

    void Application::run()
    {
        KeyPressedEvent event(57, 1);

        // Event handling
        for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
        {
            if (!event.m_handled)
            {
                (*it)->on_event(event);
            }
        }
    }
}