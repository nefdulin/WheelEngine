#include "Renderer.h"
#include "RenderCommand.h"

namespace Wheel {

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::BeginScene()
    {

    }

    void Renderer::OnScreenResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(width, height);
    }

    void Renderer::DrawIndexed(VertexArray *va)
    {
        RenderCommand::DrawIndexed(va);
    }

    void Renderer::EndScene()
    {

    }
}
