#include "OpenGLRendererAPI.h"
#include <GLAD/glad.h>

namespace Wheel {

    void OpenGLRendererAPI::SetClearColor()
    {
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const VertexArray *va)
    {
        va->Bind();
        glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}