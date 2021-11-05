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

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        WHEEL_CORE_INFO("{0}", e.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
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

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay )
    {
        m_LayerStack.PushOverlay(overlay);
    }
}