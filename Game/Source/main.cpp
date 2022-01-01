#include <iostream>
#include <Wheel.h>
#include <imgui.h>

class ExampleLayer : public Wheel::Layer
{
    virtual void OnUpdate() override
    {
        if (Wheel::Input::IsKeyPressed(Wheel::Key::Tab))
            WHEEL_INFO("Tab pressed");
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Example Layer");
        ImGui::Text("Test stuff");
        ImGui::End();
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