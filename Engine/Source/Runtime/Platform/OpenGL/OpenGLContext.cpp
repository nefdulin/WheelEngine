#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Core.h"
#include "OpenGLContext.h"

namespace Wheel {

    OpenGLContext::OpenGLContext(GLFWwindow* window) : m_WindowHandle(window)
    {

    }

    void Wheel::OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);

        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        WHEEL_CORE_ASSERT(status, "Failed to initialize glad!");

        WHEEL_CORE_INFO("OpenGL Info:");
        WHEEL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        WHEEL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        WHEEL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void Wheel::OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
