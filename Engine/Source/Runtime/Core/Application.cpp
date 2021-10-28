#include "Application.h"
#include "Events/ApplicationEvent.h"

namespace Wheel {

    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        AppUpdateEvent newUpdateEvent;
        std::cout << newUpdateEvent.GetName() << std::endl;
        while (true)
        {
            //std::cout << "Running" << std::endl;
        }
    }
}