#include "MacWindow.h"

namespace Wheel {

    class WindowsWindow : public Window
    {

    };

    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps &props)
    {
        return new MacWindow(props);
    }

    MacWindow::MacWindow(const WindowProps &props)
    {
        Init(props);
    }

    MacWindow::~MacWindow()
    {
        Shutdown();
    }

    void MacWindow::Init(const WindowProps& props)
    {
        m_Data.title = props.title;
        m_Data.width = props.width;
        m_Data.height = props.height;

        WHEEL_CORE_INFO("Creating window {0} {1} {2}", m_Data.title, m_Data.width, m_Data.height);

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            WHEEL_CORE_ASSERT(success, "GLFW Initialization failed");

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int) m_Data.width, (int) m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void MacWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void MacWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void MacWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool MacWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

}