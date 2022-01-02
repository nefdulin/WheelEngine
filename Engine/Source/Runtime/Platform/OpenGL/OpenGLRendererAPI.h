#pragma once
#include "Renderer/RendererAPI.h"

namespace Wheel {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void SetClearColor() override;
        void Clear() override;

        void DrawIndexed(const VertexArray* va) override;
    };
}
