#pragma once
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Wheel {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow*);

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };
}


