#pragma once
#include <glm/glm.hpp>
// We need this for mac builds dont know why, file is already included in unordered map...
#include <unordered_map>

namespace Wheel {

    enum ShaderSourceType
    {
        INVALID = -1, 
        VERTEX,
        PIXEL
    };

    typedef std::unordered_map<ShaderSourceType, std::string> ShaderSourceMap;

    class Shader
    {
        friend class ShaderLibrary;
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const std::string& GetName() const = 0;

        virtual void SetInt(const std::string& name, const int& value) const = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) const = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) const = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value)   const = 0;

        static std::string GetNameFromType(ShaderSourceType type); 
        static ShaderSourceType GetTypeFromName(const std::string& name);

        static std::string ReadFromFile(const std::string& path);
        static ShaderSourceMap Parse(const std::string& source);

    public:
        static Ref<Shader> Create(const std::string& name, const std::string& path);
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
    };

    typedef std::unordered_map<std::string, Ref<Shader>> ShaderMap;

    class ShaderLibrary
    {
    public:
        void Add(Ref<Shader> shader);
        Ref<Shader> Load(const std::string& path);
        Ref<Shader> Load(const std::string& name, const std::string& path);
        Ref<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const; 

    private:
        ShaderMap m_Shaders;
    };

} 