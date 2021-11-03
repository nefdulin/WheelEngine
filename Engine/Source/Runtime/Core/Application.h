#pragma once
#include "Window.h"

namespace Wheel {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // Will be defined by the CLIENT
    Application* CreateApplication();
}

