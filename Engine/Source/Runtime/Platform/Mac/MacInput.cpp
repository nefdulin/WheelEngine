#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include <GLFW/glfw3.h>

#ifdef WHEEL_PLATFORM_WINDOWS

namespace Wheel {

    bool Input::IsKeyPressed(int keycode)
    {
        auto* window = static_cast<GLFWwindow*>(Wheel::Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<uint32_t>(keycode));

        return state == GLFW_PRESS | state == GLFW_REPEAT;
    }
}

#endif
