#include "Core/Core.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Wheel {

    Ref<VertexBuffer> VertexBuffer::CreateVertexBuffer(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:   WHEEL_CORE_ASSERT(false, "None is not a supported API"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        }

        WHEEL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::CreateIndexBuffer(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:   WHEEL_CORE_ASSERT(false, "None is not a supported API"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
        }

        WHEEL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
