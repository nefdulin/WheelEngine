#include "Renderer.h"
#include "RenderCommand.h"
#include "Renderer2D.h"
#include "Mesh.h"

namespace Wheel {

    static Renderer::RendererData* s_Data = nullptr;

    void Renderer::Init(uint32_t width, uint32_t height)
    {
        s_Data = new RendererData();

        s_Data->Width = width;
        s_Data->Height = height;
        s_Data->CameraData = CreateRef<CameraData>();

        s_Data->MeshShader = Shader::Create("mesh_shader", "assets/shaders/mesh_shader.glsl");
        s_Data->ModelShader = Shader::Create("model_shader", "assets/shaders/model_shader.glsl");

        s_Data->DefaultTexture = Texture2D::Create(1, 1);
        uint32_t textureData = 0xFFFFFFFF;
        s_Data->DefaultTexture->SetData(&textureData, sizeof(uint32_t));

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::BeginScene(const glm::mat4& viewProjectionMatrix)
    {
        s_Data->MeshShader->Bind();
        s_Data->ModelShader->Bind();
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

    void Renderer::DrawSprite(const glm::mat4& transform, const Ref<Texture2D>& texture)
    {
        Renderer2D::DrawSprite(transform, texture);
    }

    void Renderer::DrawModel(const Ref<Model>& model)
    {
        for (const Ref<Mesh>& mesh : model->GetMeshes())
        {
            DrawMesh(mesh);
        }
    }

    void Renderer::DrawModel(const glm::mat4& transform, const Ref<Model>& model)
    {
        s_Data->ModelShader->Bind();
        s_Data->ModelShader->SetMat4("u_MVP", s_Data->CameraData->ViewProjection * transform);
        
        DrawModel(model);
    }

    void Renderer::DrawMesh(const glm::mat4& transform, const Ref<Mesh>& mesh, const glm::vec4& color)
    {
        s_Data->MeshShader->Bind();

        s_Data->MeshShader->SetMat4("u_MVP", s_Data->CameraData->ViewProjection * transform);
        s_Data->MeshShader->SetFloat4("u_Color", color);

        s_Data->DefaultTexture->Bind(0);
        s_Data->MeshShader->SetInt("u_Texture", 0);

        RenderCommand::DrawIndexed(mesh->GetVertexArray());
    }

    void Renderer::DrawMesh(const Ref<Mesh>& mesh)
    {
        int diffuseCounter = 1;
        int specularCounter = 1;
        int normalCounter = 1;
        int heightCounter = 1;
        auto textures = mesh->GetTextures();
        for (int i = 0; i < textures.size(); i++)  
        {
            int textureNo = -1;
            if (textures[i]->GetType() == TextureType::DIFFUSE)
                textureNo = diffuseCounter++;
            else if (textures[i]->GetType() == TextureType::SPECULAR)
                textureNo = specularCounter++;
            else if (textures[i]->GetType() == TextureType::NORMAL)
                textureNo = normalCounter++;
            else if (textures[i]->GetType() == TextureType::HEIGHT)
                textureNo = heightCounter++;

            WHEEL_CORE_ASSERT(textureNo != -1, "Invalid texture no id");

            std::string name = "texture_" + TextureTypeToName(textures[i]->GetType()) + std::to_string(textureNo);
            s_Data->ModelShader->SetInt(name, i);
            textures[i]->Bind(i);
        }

        RenderCommand::DrawIndexed(mesh->GetVertexArray());
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
