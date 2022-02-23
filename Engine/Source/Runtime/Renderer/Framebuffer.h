#pragma once

namespace Wheel {

	struct FramebufferSpecification
	{
		uint32_t Width;
		uint32_t Height;

		uint32_t Samples = 1;

		bool SwapChainTarget = 0;
	};

	class Framebuffer 
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};

}