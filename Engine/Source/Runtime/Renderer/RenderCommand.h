#pragma once
#include "RendererAPI.h"
#include <glm/glm.hpp>

namespace Wheel {

    class RenderCommand
    {
    public:
        static void Init();
        static void Clear();
        static void SetViewport(uint32_t width, uint32_t height);
        static void SetClearColor(const glm::vec4& color);
        static void DrawIndexed(const VertexArray* va);
    private:
        static RendererAPI* s_RendererAPI;
    };
}