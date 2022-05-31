#pragma once

extern Wheel::Application* Wheel::CreateApplication();

int main(int argc, char** argv)
{
    Wheel::Log::Init();
    auto app = Wheel::CreateApplication();
    app->Run();
    delete app;
}