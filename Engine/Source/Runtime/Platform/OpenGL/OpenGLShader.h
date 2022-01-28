#pragma once 
#include "Renderer/Shader.h"

namespace Wheel {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader();
		OpenGLShader(const std::string& name, const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const { return m_Name; }

		virtual void SetInt(const std::string& name, const int& value) const override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) const override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) const override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value)	const override;

	private:
		void CompileShaders(const std::unordered_map<ShaderSourceType, std::string>& shaders);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}