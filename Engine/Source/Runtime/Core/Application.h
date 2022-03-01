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
        Application(const std::string& name, uint32_t width, uint32_t height);
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

        void Close() { m_Running = false;  }
    private:
        std::unique_ptr<Window> m_Window;
        Ref<ImGuiLayer> m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        bool m_Minimized;
        float m_LastFrame;

    private:
        static Application* s_Instance;
    };

    // Will be defined by the CLIENT
    Application* CreateApplication();
}

