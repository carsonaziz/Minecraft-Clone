#pragma once

#include "event.h"
#include <sstream>

namespace Minecraft
{
    class WindowResizeEvent : public Event
    {
    private:
        unsigned int m_width, m_height;

    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

        inline unsigned int get_width() const { return m_width; }
        inline unsigned int get_height() const { return m_height; }

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_width << ", " << m_height;
            return ss.str();
        }

        static EventType get_static_type() { return EventType::WindowResize; }
        virtual EventType get_event_type() const override { return get_static_type(); }
        virtual const char* get_name() const override { return "WindowResize"; }
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        static EventType get_static_type() { return EventType::WindowClose; }
        virtual EventType get_event_type() const override { return get_static_type(); }
        virtual const char* get_name() const override { return "WindowClose"; }
    };
}