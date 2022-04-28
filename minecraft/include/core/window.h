#pragma once

#include <memory>
#include <string>

#include "core/events/event.h"

struct GLFWwindow;

namespace Minecraft
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width, Height;

        WindowProps(std::string title = "Minecraft", unsigned int width = 1280, unsigned int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class Window
    {
    private:
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool Vsync;
            std::function<void(Event& event)> EventCallback;
        };

        GLFWwindow* m_window;
        WindowData m_data;

    private:
        void init(const WindowProps& props);
        void shutdown();
        
        static void error_callback(int error, const char* description);
    public:
        Window(const WindowProps& props = WindowProps());
        ~Window();

        void set_vsync(bool vsync);
        void swap_and_poll();

        void set_event_callback(const std::function<void(Event& e)>& callback);
    };
}