#pragma once 
#include "Renderer/Shader.h"

namespace Wheel {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader();
		OpenGLShader(const std::string& vertexFilePath, const std::string& fragmentFilePath);

		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetFloat3(const std::string& name, const glm::vec3& value) const override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) const override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value)	const override;
	private:
		uint32_t m_RendererID;
	};

}