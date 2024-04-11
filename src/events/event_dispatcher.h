#pragma once

#include <functional>
#include "events/event.h"
#include "events/application_event.h"

class EventDispatcher
{
public:
    EventDispatcher(Event &_event) : event(_event) {}

    template<typename T>
    bool Dispatch(std::function<void()> func) {
        if (event.GetEventType() == T::GetEventType())
            func(static_cast<T&>(event));
    }

private:
    Event &event;
};
