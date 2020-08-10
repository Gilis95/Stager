#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "event/ApplicationEvent.h"
#include "window/glfw/PlatformIndependentWindow.h"

#include "stinkypch.h"


namespace stinky
{

    /////////////////////////////////////////////////////////////////////////////////////////
    static void GLFWErrorCallback(int error, const char* description)
    {
        STINKY_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    PlatformIndependentWindow::PlatformIndependentWindow(const WindowProperties& properties)
    {
        m_Data.height = properties.m_Height;
        m_Data.width = properties.m_Width;
        m_Data.titile = properties.m_Title;

        Init();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    PlatformIndependentWindow::~PlatformIndependentWindow()
    {
        Shutdown();
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    void PlatformIndependentWindow::Init()
    {

        int status = glfwInit();

        AssertReturnUnless(status);
        glfwSetErrorCallback(GLFWErrorCallback);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.titile.c_str(), NULL, NULL);

        // create context for current window
        glfwMakeContextCurrent(m_Window);

        glfwSwapInterval(5);

        AssertReturnUnless(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

        glfwSetWindowUserPointer(m_Window, &m_Data);

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                data.eventHandlerFn(WindowCloseEvent());
            }
        );

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PlatformIndependentWindow::SetEventCallback(EventHandler::EventHandlerFn eventHandlerFn)
    {
        m_Data.eventHandlerFn = eventHandlerFn;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PlatformIndependentWindow::OnUpdate(const Event& onUpdateEvent)
    {

        // swap front and back buffer
        glfwSwapBuffers(m_Window);

        //poll for process events
        glfwPollEvents();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PlatformIndependentWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}