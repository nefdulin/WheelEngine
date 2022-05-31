#include <iostream>
#include <Wheel.h>
#include <imgui.h>
#include <Core/EntryPoint.h>
#include "EditorLayer.h"

namespace Wheel {

    class EditorApp : public Wheel::Application
    {
    public:
        EditorApp(const std::string& name, uint32_t width, uint32_t height)
                : Wheel::Application(name, width, height)
        {
            Wheel::Layer* l2 = new EditorLayer();
            PushLayer(l2);
        }

        ~EditorApp()
        {

        }
    };

    Wheel::Application* Wheel::CreateApplication()
    {
        return new EditorApp("Wheel Editor", 1280, 720);
    }
}