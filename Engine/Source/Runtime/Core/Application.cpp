#include "Application.h"
#include "Log.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer/OrthographicCamera.h"

namespace Wheel {

    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& name, uint32_t width, uint32_t height)
    {
        WHEEL_CORE_ASSERT(s_Instance == nullptr, "An application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create({name, width, height}));
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        Renderer::Init(m_Window->GetWidth(), m_Window->GetHeight());

        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer.get());

        m_LastFrame = 0.0f;
        m_Minimized = false;
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

            if (!m_Minimized)
            {
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(deltaTime);

                m_ImGuiLayer->Begin();
                for (Layer* layer : m_LayerStack)
                    layer->OnImGuiRender();
                m_ImGuiLayer->End();
            }

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
            if (e.Handled)
                break;
            (*--it)->OnEvent(e);
        }
    }

    bool Application::OnMouseMoved(MouseMovedEvent& e)
    {
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnScreenResize(e.GetWidth(), e.GetHeight());

        return false;
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