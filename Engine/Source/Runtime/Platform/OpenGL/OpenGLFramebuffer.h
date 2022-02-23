#pragma once
#include "Renderer/Framebuffer.h"

namespace Wheel {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec) : 
			m_Specification(spec)
		{
			Invalidate();
		}

		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { return m_ColorAttachmentID;  }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		void Invalidate();

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachmentID = 0;
		uint32_t m_DepthAttachmentID = 0;
		FramebufferSpecification m_Specification;
	};

}