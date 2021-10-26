#pragma once

namespace Wheel {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // Will be defined by the CLIENT
    Application* CreateApplication();
}

