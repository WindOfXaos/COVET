#pragma once

#include <string>
#include <sstream>

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
    virtual ~Event() = default;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual std::string ToString() const { return GetName(); }
};