#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Wheel {

	Shader* Shader::Create(const std::string& vertexFilePath, const std::string& fragmentFilePath)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:	WHEEL_CORE_ASSERT(false, "Invalid Renderer API."); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexFilePath, fragmentFilePath);
		}
	}
	
} 