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
        bool my_tool_active = true;
        float my_color[4];
        ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
                if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

// Edit a color (stored as ~4 floats)
        ImGui::ColorEdit4("Color", my_color);

// Plot some values
        const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
        ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

// Display contents in a scrolling region
        ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
        ImGui::BeginChild("Scrolling");
        for (int n = 0; n < 50; n++)
            ImGui::Text("%04d: Some text", n);
        ImGui::EndChild();
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