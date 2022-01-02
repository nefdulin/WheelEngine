#include "RendererAPI.h"
#include "Core/Core.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Wheel {

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    RendererAPI* RendererAPI::Create()
    {
        switch (s_API)
        {
            case RendererAPI::API::None: WHEEL_CORE_ASSERT(false, "None is not a supported RendererAPI"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLRendererAPI();
        }
    }
}


