#pragma once

#include "event.h"

#include <sstream>

namespace Minecraft
{
    class MouseMovedEvent : public Event
    {
    private:
        float m_mousex, m_mousey;

    public:
        MouseMovedEvent(float x, float y) : m_mousex(x), m_mousey(y) {}

        inline float get_x() const { return m_mousex; }
        inline float get_y() const { return m_mousey; }

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_mousex << ", " << m_mousey;
            return ss.str();
        }

        static EventType get_static_type() { return EventType::MouseMoved; }
        virtual EventType get_event_type() const override { return get_static_type(); }
        virtual const char* get_name() const override { return "MouseMoved"; }
    };

    class MouseScrolledEvent: public Event
    {
    private:
        float m_xoffset, m_yoffset;

    public:
        MouseScrolledEvent(float xoffset, float yoffset) : m_xoffset(xoffset), m_yoffset(yoffset) {}

        inline float get_xoffset() const { return m_xoffset; }
        inline float get_yoffset() const { return m_yoffset; }

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << get_xoffset() << ", " << get_yoffset();
            return ss.str();
        }

        static EventType get_static_type() { return EventType::MouseScrolled; }
        virtual EventType get_event_type() const override { return get_static_type(); }
        virtual const char* get_name() const override { return "MouseScrolled"; }
    };

    class MouseButtonEvent : public Event
    {
    protected:
        int m_button;

    protected:
        MouseButtonEvent(int button) : m_button(button) {}
    public:
        inline int get_mouse_button() const { return m_button; }
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_button;
            return ss.str();
        }

        static EventType get_static_type() { return EventType::MouseButtonPressed; }
        virtual EventType get_event_type() const override { return get_static_type(); }
        virtual const char* get_name() const override { return "MouseButtonPressed"; }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_button;
            return ss.str();
        }

        static EventType get_static_type() { return EventType::MouseButtonReleased; }
        virtual EventType get_event_type() const override { return get_static_type(); }
        virtual const char* get_name() const override { return "MouseButtonReleased"; }
    };
}