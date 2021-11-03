#pragma once
#include "Window.h"
#include "Events/ApplicationEvent.h"

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
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // Will be defined by the CLIENT
    Application* CreateApplication();
}

