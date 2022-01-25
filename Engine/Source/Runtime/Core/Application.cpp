#include "Application.h"
#include "Log.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer/OrthographicCamera.h"

namespace Wheel {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        WHEEL_CORE_ASSERT(s_Instance == nullptr, "An application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer.get());

        m_LastFrame = 0.0f;
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {       
        while (m_Running)
        {
            float currentTime = m_Window->GetTime();
            float deltaTime = currentTime - m_LastFrame;

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();

            m_LastFrame = currentTime;
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Application::OnMouseMoved, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    bool Application::OnMouseMoved(MouseMovedEvent& e)
    {
        return true;
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
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
}