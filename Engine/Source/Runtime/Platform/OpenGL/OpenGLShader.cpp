#include "Core/Core.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glad/glad.h>

namespace Wheel {

    static GLenum GetOpenGLShaderTypeFromShaderSourceType(ShaderSourceType type)
    {
        switch (type)
        {
            case ShaderSourceType::VERTEX:
                return GL_VERTEX_SHADER;
            case ShaderSourceType::PIXEL:
                return GL_FRAGMENT_SHADER;
        }
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& path) :
        m_Name(name)
    {
        std::string source = Shader::ReadFromFile(path);
        ShaderSourceMap shaders = Shader::Parse(source);
        CompileShaders(shaders);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) :
        m_Name(name)
    {
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::CompileShaders(const ShaderSourceMap& shaders)
    {
        uint32_t program = glCreateProgram();

        std::array<uint32_t, 2> shaderIDs;
        uint32_t index = 0;
        for (auto&& [key, value] : shaders)
        {
            // Create an empty vertex shader handle
            GLuint shader = glCreateShader(GetOpenGLShaderTypeFromShaderSourceType(key));

            // Send the vertex shader source code to GL
            // Note that std::string's .c_str is NULL character terminated.
            const GLchar* source = value.c_str();
            glShaderSource(shader, 1, &source, 0);

            // Compile the vertex shader
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                WHEEL_CORE_ERROR("{0}", infoLog.data());
                WHEEL_CORE_ASSERT(false, "{0} Shader compilation failure!", key);
                return;
            }

            glAttachShader(program, shader);
            shaderIDs[index++] = shader;
        }

        // Link our program
        m_RendererID = program;

        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            glDeleteProgram(program);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            WHEEL_CORE_ERROR("{0}", infoLog.data());
            WHEEL_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto& shader : shaderIDs)
        {
            glDeleteShader(shader);
            glDetachShader(program, shader);
        }

    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) const 
    {
        glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void OpenGLShader::SetInt(const std::string& name, const int& value) const
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

}