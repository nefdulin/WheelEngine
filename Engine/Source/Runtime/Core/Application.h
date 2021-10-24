#pragma once
#include "Core.h"

namespace Wheel
{
    class WHEEL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // Will be defined by the CLIENT
    Application* CreateApplication();
}

