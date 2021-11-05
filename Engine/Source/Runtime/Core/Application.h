#pragma once
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

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

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

        LayerStack m_LayerStack;
    };

    // Will be defined by the CLIENT
    Application* CreateApplication();
}

