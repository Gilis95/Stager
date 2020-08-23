#pragma once

#include "event/Event.h"
#include "stinkypch.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
                : EVENT_CONSTRUCTOR(WindowResize), m_Width(width), m_Height(height) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        unsigned int m_Width, m_Height;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() : EVENT_CONSTRUCTOR(WindowClose) {}
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class AppTickEvent : public Event {
    public:
        AppTickEvent() : EVENT_CONSTRUCTOR(AppTick) {}
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() : EVENT_CONSTRUCTOR(AppUpdate) {}
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() : EVENT_CONSTRUCTOR(AppRender) {}
    };
}  // namespace stinky