#pragma once

namespace Wheel {

    enum class RendererAPI
    {
        None = 0,
        OpenGL
    };

    class Renderer
    {
    public:
        static RendererAPI GetAPI() const { return s_API; }
    private:
        static RendererAPI s_API;
    };
}
