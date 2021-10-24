#pragma once
#include "Core.h"

extern Wheel::Application* Wheel::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Wheel::CreateApplication();
    app->Run();
    delete app;
}