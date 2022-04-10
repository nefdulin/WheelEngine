#pragma once

namespace Wheel {

    class Input
    {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMousePressed(int mousecode);

        static float GetMousePositionX();
        static float GetMousePositionY();

        static glm::vec2 GetMousePosition();
    };
}

