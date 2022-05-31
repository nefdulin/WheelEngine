#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <fstream>

namespace Wheel {

	std::string Shader::GetNameFromType(ShaderSourceType type)
	{
		switch (type)
		{
			case ShaderSourceType::VERTEX:
				return "vertex";
			case ShaderSourceType::PIXEL:
				return "pixel";
		}

		WHEEL_CORE_ASSERT(false, "Invalid shader type");
		return nullptr;
	}

	ShaderSourceType Shader::GetTypeFromName(const std::string& name)
	{
		if (name == "vertex")
			return ShaderSourceType::VERTEX;
		else if (name == "pixel")
			return ShaderSourceType::PIXEL;

		WHEEL_CORE_ASSERT(true, "Invalid shader name");
		return ShaderSourceType::INVALID;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexFilePath, const std::string& fragmentFilePath)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:	WHEEL_CORE_ASSERT(false, "Invalid Renderer API."); return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(name, vertexFilePath, fragmentFilePath);
		}
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:	WHEEL_CORE_ASSERT(false, "Invalid Renderer API."); return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(name, path);
		}
	}

	std::string Shader::ReadFromFile(const std::string& path)
	{
		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			int size = in.tellg();

			if (size != -1)
			{
				in.seekg(0, std::ios::beg);
				result.resize(size);
				in.read(&result[0], size);
			}
			else
			{
				WHEEL_CORE_ASSERT(false, "Error reading shader file {0}", path.c_str());
			}
		}
		else
		{
            WHEEL_CORE_INFO("ErrorCode: {0}", strerror(errno));
			WHEEL_CORE_ASSERT(false, "Error opening shader file {0} error code: {1}", path.c_str(), strerror(errno));

		}
		
		return result;
	}


	ShaderSourceMap Shader::Parse(const std::string& source)
	{
		ShaderSourceMap shaders;
		const char* token = "#type";
		
		size_t shaderDeclaration = source.find_first_of(token, 0);
		while (shaderDeclaration != std::string::npos)
		{
			// Shader type declaration line
			size_t eol = source.find_first_of("\n\r", shaderDeclaration);
			WHEEL_CORE_ASSERT(eol != std::string::npos, "Error in shader type declaration line!");

			size_t begin = shaderDeclaration + strlen(token) + 1;
			std::string shaderSourceName = source.substr(begin, eol - begin);
			
			ShaderSourceType type = GetTypeFromName(shaderSourceName);
			WHEEL_CORE_ASSERT(type != ShaderSourceType::INVALID, "Invalid shader source type ");

			// Start of the shader source code after the declaration
			size_t nextLinePos = source.find_first_not_of("\n\r", eol);
			// Finding the start of the next shader declartion line 
			shaderDeclaration = source.find(token, nextLinePos);

			shaders[type] = (shaderDeclaration == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, shaderDeclaration - nextLinePos);
		}

		return shaders;
	}

	void ShaderLibrary::Add(const Ref<Shader> shader)
	{
		if (Exists(shader->GetName()))
		{
			WHEEL_CORE_ERROR("Shader already exists");
			return;
		}

		m_Shaders.insert(std::make_pair(shader->GetName(), shader));
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		size_t pos = path.find_last_of("\/");
		size_t dotPos = path.rfind('.');
		std::string name = path.substr(pos + 1, dotPos - pos - 1);

		WHEEL_CORE_ASSERT(!Exists(name), "Shader with the same name already exists");

		Ref<Shader> shader = Shader::Create(name, path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		if (Exists(name))
		{
			WHEEL_CORE_ASSERT(false, "Shader with the same name already exists");
			return nullptr;
		}

		Ref<Shader> shader = Shader::Create(name, path);
		Add(shader);
		return shader;
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		WHEEL_CORE_ASSERT(Exists(name), "Shader could not be found!");
		return m_Shaders[name];
	}
}
 