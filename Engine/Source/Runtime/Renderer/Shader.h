#pragma once
#include <glm/glm.hpp>

namespace Wheel {

    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetFloat3(const std::string& name, const glm::vec3& value) const = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) const = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value)   const = 0;
        
        static Shader* Create(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    };

} 