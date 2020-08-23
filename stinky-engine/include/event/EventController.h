//
// Created by christian on 23/08/2020.
//

#pragma once

#include <unordered_map>

#include "Event.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class EventController {
    private:
        using EventHandlers = std::vector<EventHandler::EventHandlerFn>;
    public:
        EventController();

        //Events
        void RegisterEvent(EventType eventType);

        void RegisterEventHandler(const EventHandler &handler);

        void OnEvent(const Event &);

    private:
        std::unordered_map<EventType, EventHandlers> m_EventHandlers;
    };
}