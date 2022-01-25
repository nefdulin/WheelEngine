#pragma once
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Camera.h"

namespace Wheel {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);
        void Run();

        bool OnWindowResize(WindowResizeEvent& e);
        bool OnWindowClose(WindowCloseEvent& e);

        bool OnMouseMoved(MouseMovedEvent& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
    private:
        std::unique_ptr<Window> m_Window;
        std::shared_ptr<ImGuiLayer> m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

    private:
        static Application* s_Instance;
    };

    // Will be defined by the CLIENT
    Application* CreateApplication();
}

