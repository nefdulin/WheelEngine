#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

namespace Wheel {

    class Renderer
    {
    public:
        struct CameraData
        {
            glm::mat4 ViewProjection;
        };

        struct RendererData
        {
            uint32_t Width;
            uint32_t Height;

            Ref<Shader> DefaultShader;

            Ref<CameraData> CameraData;
        };

    public:
        static const RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        static void Init(uint32_t width, uint32_t height);

        static void OnScreenResize(uint32_t width, uint32_t height);
        static void BeginScene(const glm::mat4& viewProjectionMatrix);
        static void BeginScene(const Camera& camera, const glm::mat4& transform);

        static void DrawQuad(const glm::vec3& position);
        static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const Ref<Texture>& texture);
        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);

        static void DrawIndexed(const Ref<VertexArray>& va);
        static void EndScene();
    };
}
