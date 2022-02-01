#include "Renderer.h"
#include "RenderCommand.h"
#include "Renderer2D.h"

namespace Wheel {

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::BeginScene()
    {

    }

    void Renderer::OnScreenResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(width, height);
    }

    void Renderer::DrawIndexed(const Ref<VertexArray>& va)
    {
        RenderCommand::DrawIndexed(va);
    }

    void Renderer::EndScene()
    {

    }
}
