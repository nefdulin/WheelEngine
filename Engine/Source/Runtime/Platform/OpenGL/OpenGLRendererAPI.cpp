#include "OpenGLRendererAPI.h"
#include <GLAD/glad.h>
#include <glm/glm.hpp>

namespace Wheel {

    void OpenGLRendererAPI::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        WHEEL_CORE_INFO("OpenGL Renderer initialized");
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t width, uint32_t height)
    {
        glViewport(0, 0, width, height);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> va)
    {
        va->Bind();
        glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}