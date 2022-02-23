#include "Renderer.h"
#include "RenderCommand.h"
#include "Renderer2D.h"

namespace Wheel {

    struct RendererData
    {
        uint32_t Width;
        uint32_t Height;
    };

    static RendererData* s_Data = nullptr;

    void Renderer::Init(uint32_t width, uint32_t height)
    {
        s_Data = new RendererData();

        s_Data->Width = width;
        s_Data->Height = height;

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
