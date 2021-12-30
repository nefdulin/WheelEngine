#include <iostream>
#include <Wheel.h>

class ExampleLayer : public Wheel::Layer
{
    virtual void OnUpdate() override
    {
        if (Wheel::Input::IsKeyPressed(Wheel::Key::Tab))
            WHEEL_INFO("Tab preseed");
    }
};

class GameApp : public Wheel::Application
{
public:
    GameApp()
    {
        Wheel::Layer* layer = new ExampleLayer();
        PushLayer(layer);
    }

    ~GameApp()
    {

    }
};

Wheel::Application* Wheel::CreateApplication()
{
    return new GameApp();
}