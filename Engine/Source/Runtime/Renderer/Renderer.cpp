#include "Renderer.h"
#include "RenderCommand.h"

namespace Wheel {

    void Renderer::BeginScene()
    {

    }

    void Renderer::DrawIndexed(VertexArray *va)
    {
        RenderCommand::DrawIndexed(va);
    }

    void Renderer::EndScene()
    {

    }
}
