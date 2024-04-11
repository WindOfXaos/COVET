#pragma once

#include "events/event.h"

class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width), m_Height(height) {}

    unsigned int GetWidth() const { return m_Width; }
    unsigned int GetHeight() const { return m_Height; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }
    virtual EventType GetEventType() const override { return EventType::WindowMoved; }
    virtual const char* GetName() const override { return "WindowMoved"; }
private:
    unsigned int m_Width, m_Height;
};

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() = default;

    virtual EventType GetEventType() const override { return EventType::WindowClose; }
    virtual const char* GetName() const override { return "WindowClose"; }
};
