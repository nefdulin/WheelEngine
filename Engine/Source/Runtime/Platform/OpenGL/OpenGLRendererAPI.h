#pragma once
#include "Renderer/RendererAPI.h"

namespace Wheel {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void SetViewport(uint32_t width, uint32_t height) override;
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;
virtual
        virtual void DrawIndexed(const VertexArray* va) override;
    };
}
