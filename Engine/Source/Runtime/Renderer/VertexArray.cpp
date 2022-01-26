#include "VertexArray.h"
#include "Renderer.h"
#include "Core/Core.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Wheel {

    Ref<VertexArray> VertexArray::CreateVertexArray()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:   WHEEL_CORE_ASSERT(false, "None is not a valid RendererAPI"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
        }

        WHEEL_CORE_ASSERT(false, "RendererAPI is not a valid API");
        return nullptr;
    }
}
