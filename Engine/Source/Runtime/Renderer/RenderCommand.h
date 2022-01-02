#pragma once
#include "RendererAPI.h"

namespace Wheel {

    class RenderCommand
    {
    public:
        static void Clear();
        static void SetClearColor();
        static void DrawIndexed(const VertexArray* va);
    private:
        static RendererAPI* s_RendererAPI;
    };
}