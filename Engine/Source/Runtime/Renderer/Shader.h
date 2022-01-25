#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Wheel {

    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;
        void SetMat4(const std::string& name, const glm::mat4& mat) const;
    private:
        uint32_t m_RendererID;
    };

} 