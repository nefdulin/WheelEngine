#include "Renderer.h"
#include "RenderCommand.h"
#include "Renderer2D.h"

namespace Wheel {

    static Renderer::RendererData* s_Data = nullptr;

    void Renderer::Init(uint32_t width, uint32_t height)
    {
        s_Data = new RendererData();

        s_Data->Width = width;
        s_Data->Height = height;
        s_Data->CameraData = CreateRef<CameraData>();

        s_Data->DefaultShader = Shader::Create("default2D", "assets/shaders/default2D.glsl");

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::BeginScene(const glm::mat4& viewProjectionMatrix)
    {
        s_Data->CameraData->ViewProjection = viewProjectionMatrix;

        Renderer2D::BeginScene(viewProjectionMatrix);
    }

    void Renderer::BeginScene(const Camera& camera, const glm::mat4& transform)
    {
        s_Data->CameraData->ViewProjection = camera.GetProjectionMatrix() * glm::inverse(transform);

        Renderer2D::BeginScene(camera, transform);
    }

    void Renderer::DrawQuad(const glm::vec3& position)
    {
        Renderer2D::DrawQuad(position, glm::vec3(1.0f));
    }

    void Renderer::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color)
    {
        Renderer2D::DrawQuad(position, scale, color);
    }

    void Renderer::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const Ref<Texture>& texture)
    {
        Renderer2D::DrawQuad(position, scale, texture);
    }

    void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        Renderer2D::DrawQuad(transform, color);
    }

    void Renderer::OnScreenResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(width, height);
    }

    void Renderer::DrawIndexed(const Ref<VertexArray>& va)
    {
        RenderCommand::DrawIndexed(va);
    }

    void Renderer::EndScene()
    {
        Renderer2D::EndScene();
    }
}
