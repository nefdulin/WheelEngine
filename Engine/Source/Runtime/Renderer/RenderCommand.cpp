#include "RenderCommand.h"

namespace Wheel {

    RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();

    void RenderCommand::Clear()
    {
        s_RendererAPI->Clear();
    }

    void RenderCommand::SetClearColor()
    {
        s_RendererAPI->SetClearColor();
    }

    void RenderCommand::DrawIndexed(const VertexArray* va)
    {
        s_RendererAPI->DrawIndexed(va);
    }

}
