#pragma once
#include "VertexArray.h"

namespace Wheel {

    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL
        };

    public:
        virtual ~RendererAPI() = default;

        virtual void Clear() = 0;
        virtual void SetClearColor() = 0;

        virtual void DrawIndexed(const VertexArray* va) = 0;

        static API GetAPI() { return s_API; }
        static RendererAPI* Create();
    private:
        static API s_API;
    };

}



