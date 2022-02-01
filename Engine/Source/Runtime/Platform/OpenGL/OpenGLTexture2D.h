#pragma once
#include "Renderer/Texture.h"

namespace Wheel {

	typedef unsigned int GLenum;

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);

		~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual void SetData(const void* data, uint32_t size);

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		uint32_t m_RendererID;

		uint32_t m_Width;
		uint32_t m_Height;

		GLenum m_InternalFormat;
		GLenum m_DataFormat;
	};

}
