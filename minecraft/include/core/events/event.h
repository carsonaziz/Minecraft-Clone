#pragma once

#include <string>

namespace Minecraft
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    class Event
    {
    public:
        bool m_handled = false;

    public:
        virtual EventType get_event_type() const = 0;
        virtual const char* get_name() const = 0;
        virtual std::string to_string() const { return get_name(); }
    };

    class EventHandler
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    private:
        Event& m_event;

    public:
        EventHandler(Event& event) : m_event(event) {}

        template<typename T>
        bool handle_event(EventFn<T> func)
        {
            if (m_event.get_event_type() == T::get_static_type())
            {
                m_event.m_handled = func(*(T*)&m_event);
                return true;
            }
            return false;
        }
    };
}