#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"

namespace Wheel {

    class Renderer
    {
    public:
        static const RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        static void Init();

        static void OnScreenResize(uint32_t width, uint32_t height);
        static void BeginScene();
        static void DrawIndexed(VertexArray* va);
        static void EndScene();
    };
}
