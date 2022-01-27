#include "OpenGLTexture2D.h"
#include <glad/glad.h>
#include <stb_image.h>

namespace Wheel {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        WHEEL_CORE_ASSERT(data, "Couldn't load the texture");
        m_Width = width;
        m_Height = height;

        // Since functions like glTextureStorage2D are not supported in openGL 4.1
#ifdef WHEEL_PLATFORM_MAC
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
#else
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);
#endif
        stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
#ifdef WHEEL_PLATFORM_MAC
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
#else
		glBindTextureUnit(slot, m_RendererID);
#endif
	}

}