#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include <GLFW/glfw3.h>

namespace Wheel {

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        while (m_Running)
        {
            //glClearColor(1, 0, 1, 1);
            //glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        WHEEL_CORE_INFO("{0}", e.ToString());
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        WHEEL_CORE_TRACE("Window resizing");
        return true;
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        WHEEL_CORE_ERROR("Window close event triggered, application stopped!");
        m_Running = 0;
        return true;
    }
}