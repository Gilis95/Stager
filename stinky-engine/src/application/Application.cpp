#include "application/Application.h"


#include "stinkypch.h"
#include "event/ApplicationEvent.h"

#include "event/Event.h"
#include "GLFW/glfw3.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    Application::Application(Window::API windowApi) : m_IsRunning(false){
        Init(windowApi);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Application::~Application() {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Init(Window::API windowApi)
    {
        Log::init();

        m_Window = Window::Create(windowApi);

        m_Window->SetEventCallback(STINKY_BIND(Application::OnEvent));

        // KeyPressed, KeyReleased, KeyTyped,
        RegisterEvent(EventType::KeyPressed);
        RegisterEvent(EventType::KeyReleased);
        RegisterEvent(EventType::KeyTyped);

        // MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled 
        RegisterEvent(EventType::MouseButtonPressed);
        RegisterEvent(EventType::MouseButtonReleased);
        RegisterEvent(EventType::MouseMoved);
        RegisterEvent(EventType::MouseScrolled);


        // WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        RegisterEvent(EventType::WindowClose);
        RegisterEvent(EventType::WindowResize);
        RegisterEvent(EventType::WindowFocus);
        RegisterEvent(EventType::WindowLostFocus);
        RegisterEvent(EventType::WindowMoved);

        //AppTick, AppUpdate, AppRender,
        RegisterEvent(EventType::AppRender);
        RegisterEvent(EventType::AppTick);
        RegisterEvent(EventType::AppUpdate);

        RegisterEventHandler({ 
            EventType::WindowClose,
            STINKY_BIND(Application::Close)
        });

        RegisterEventHandler({
            EventType::AppUpdate,
            std::bind(&Window::OnUpdate, m_Window.get(), std::placeholders::_1)
        });
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Close(const Event& closeEvent)
    {
        m_IsRunning = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::Run()
    {
        m_IsRunning = true;

        while (m_IsRunning)
        {
            //TODO:: Use platform independent tool
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            std::for_each(
                m_LayerStack.begin(), 
                m_LayerStack.end(), 
                [&](Layer* layer)->void
                {
                    layer->OnUpdate(timestep);
                });

            OnEvent(AppUpdateEvent());
        }

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::RegisterEvent(EventType type)
    {
        if(m_EventHandlers.find(type) == m_EventHandlers.end())
        {
            m_EventHandlers[type] = EventHandlers();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::RegisterEventHandler(EventHandler handler)
    {
        m_EventHandlers[handler.m_EventType].push_back(handler.m_EventHandlerFunction);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Application::OnEvent(const Event& event)
    {
        auto handlers = m_EventHandlers.find(event.GetEventType());

        if(handlers!=m_EventHandlers.end())
        {
            std::for_each(
                handlers->second.begin(), 
                handlers->second.end(), 
                [&](EventHandler::EventHandlerFn& handlerFunction) -> void
            {
                    handlerFunction(event);
            });
        }
    }
}