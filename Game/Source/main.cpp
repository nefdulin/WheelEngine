#include <iostream>
#include <Wheel.h>

class GameApp : public Wheel::Application
{
public:
    GameApp()
    {
        PushOverlay(new Wheel::ImGuiLayer());
    }

    ~GameApp()
    {

    }
};

Wheel::Application* Wheel::CreateApplication()
{
    return new GameApp();
}