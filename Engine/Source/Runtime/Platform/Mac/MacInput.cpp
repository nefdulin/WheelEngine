#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include <GLFW/glfw3.h>

//Will add platform support later
//#ifdef

namespace Wheel {

    bool Input::IsKeyPressed(int keycode)
    {
        auto* window = static_cast<GLFWwindow*>(Wheel::Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<uint32_t>(keycode));

        return state == GLFW_PRESS | state == GLFW_REPEAT;
    }

    bool Input::IsMousePressed(int mousecode)
    {
        auto* window = static_cast<GLFWwindow*>(Wheel::Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<uint32_t>(mousecode));

        return state == GLFW_PRESS | state == GLFW_REPEAT;
    }

    float Input::GetMousePositionX()
    {
        double xpos, ypos;
        auto* window = static_cast<GLFWwindow*>(Wheel::Application::Get().GetWindow().GetNativeWindow());
        glfwGetCursorPos(window, &xpos, &ypos);

        return (float) xpos;
    }

    float Input::GetMousePositionY()
    {
        double xpos, ypos;
        auto* window = static_cast<GLFWwindow*>(Wheel::Application::Get().GetWindow().GetNativeWindow());
        glfwGetCursorPos(window, &xpos, &ypos);

        return (float) ypos;
    }

    glm::vec2 Input::GetMousePosition()
    {
        double posx, posy;
        auto* window = static_cast<GLFWwindow*>(Wheel::Application::Get().GetWindow().GetNativeWindow());
        glfwGetCursorPos(window, &posx, &posy);

        return {(float) posx, (float) posy};
    }
}

//#endif
