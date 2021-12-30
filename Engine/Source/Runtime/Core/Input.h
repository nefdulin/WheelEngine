#pragma once

namespace Wheel {

    class Input
    {
    public:
        static bool IsKeyPressed(int keycode);
        static std::pair<float, float> GetMouseButtonPosition();
    };

}

