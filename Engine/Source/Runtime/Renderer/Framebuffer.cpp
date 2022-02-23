#pragma once
#include "Renderer.h"
#include "Framebuffer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Wheel {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: WHEEL_CORE_ASSERT(false, "None is not a supported API"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
		}

		WHEEL_CORE_ASSERT(false, "Invalid RendererAPI");
		return nullptr;
	}

}
