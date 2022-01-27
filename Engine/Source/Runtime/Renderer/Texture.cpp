#include "Texture.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Wheel {
	
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: WHEEL_ASSERT(false, "Invalid Renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path); 
		}

		WHEEL_ASSERT(false, "Invalied Renderer API");
		return nullptr;
	}
	
}