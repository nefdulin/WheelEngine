#include <iostream>
#include <Wheel.h>

class GameApp : public Wheel::Application
{
public:
    GameApp()
    {

    }

    ~GameApp()
    {

    }
};

Wheel::Application* Wheel::CreateApplication()
{
    return new GameApp();
}