#pragma once

#include "event.h"

#include <sstream>

namespace Minecraft
{
    class KeyEvent : public Event
    {
    protected:
        int m_keycode;

    public:
        inline int get_key_code() const { return m_keycode; }
    protected:
        KeyEvent(int keycode) : m_keycode(keycode) {}
    };

    class KeyPressedEvent : public KeyEvent
    {
    private:
        int m_repeat_count;

    public:
        KeyPressedEvent(int keycode, int repeat_count) : KeyEvent(keycode), m_repeat_count(repeat_count) {}

        inline int get_repeat_count() const { return m_repeat_count; }

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeat_count << " repeats)";
            return ss.str();
        }

        static EventType get_static_type() { return EventType::KeyPressed; }
        virtual EventType get_event_type() const override { return get_static_type(); }
        virtual const char* get_name() const override { return "KeyPressed"; }
    };

    class KeyReleasedEvent : public KeyEvent
    {   
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keycode;
            return ss.str();
        }

        static EventType get_static_type() { return EventType::KeyReleased; }
        virtual EventType get_event_type() const override { return get_static_type(); }
        virtual const char* get_name() const override { return "KeyReleased"; }
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

        std::string to_string() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_keycode;
            return ss.str();
        }

        static EventType get_static_type() { return EventType::KeyTyped; }
        virtual EventType get_event_type() const override { return get_static_type(); }
        virtual const char* get_name() const override { return "KeyTyped"; }
    };
}