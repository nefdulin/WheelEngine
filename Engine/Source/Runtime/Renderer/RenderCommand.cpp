#include "RenderCommand.h"

namespace Wheel {

    RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();

    void RenderCommand::Clear()
    {
        s_RendererAPI->Clear();
    }

    void RenderCommand::SetClearColor(const glm::vec4& color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    void RenderCommand::DrawIndexed(const VertexArray* va)
    {
        s_RendererAPI->DrawIndexed(va);
    }

}
