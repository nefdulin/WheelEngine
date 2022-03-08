#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "glm/ext/matrix_transform.hpp"

namespace Wheel
{
	struct Renderer2DData
	{
		Ref<ShaderLibrary> ShaderLibrary;
		Ref<Shader> DefaultShader;

		Ref<VertexArray> QuadVertexArray;
		Ref<Texture> DefaultTexture;

		struct CameraData
		{
			glm::mat4 ViewProjection;
		};

		Ref<CameraData> CameraBuffer;
	};

	static Renderer2DData* s_Data = nullptr;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DData();

		s_Data->QuadVertexArray = VertexArray::CreateVertexArray();

		float vertices[] = {
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f  
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		Ref<VertexBuffer> vb = VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices));

		BufferLayout layout{
			{ShaderDataType::Float3, "a_Positions"},
			{ShaderDataType::Float2, "a_TexCoords"}
		};
		
		vb->SetLayout(layout);

		Ref<IndexBuffer> ib = IndexBuffer::CreateIndexBuffer(indices, sizeof(indices));

		s_Data->QuadVertexArray->AddVertexBuffer(vb);
		s_Data->QuadVertexArray->SetIndexBuffer(ib);
		
		s_Data->ShaderLibrary = CreateRef<ShaderLibrary>();
		s_Data->DefaultShader = s_Data->ShaderLibrary->Load("default2D", "assets/shaders/default2D.glsl");

		s_Data->CameraBuffer = CreateRef<Renderer2DData::CameraData>();

		s_Data->DefaultTexture = Texture2D::Create(1, 1);
		uint32_t textureData = 0xFFFFFFFF;
		s_Data->DefaultTexture->SetData(&textureData, sizeof(uint32_t));
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const Ref<Camera>& camera)
	{
		s_Data->DefaultShader->Bind();

		s_Data->CameraBuffer->ViewProjection = camera->GetViewProjectionMatrix();
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& color)
	{
        Renderer2D::DrawQuad(glm::vec3(position, 1.0f), color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& scale)
	{
		s_Data->DefaultShader->Bind();
		s_Data->QuadVertexArray->Bind();

		s_Data->DefaultShader->SetMat4("u_MVP", s_Data->CameraBuffer->ViewProjection * glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1), scale));

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color)
	{
		s_Data->DefaultShader->Bind();

		s_Data->DefaultShader->SetMat4("u_MVP", s_Data->CameraBuffer->ViewProjection * glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale));
		s_Data->DefaultShader->SetFloat4("u_Color", color);

		s_Data->DefaultTexture->Bind(0);
		s_Data->DefaultShader->SetInt("u_Texture", 0);

		s_Data->QuadVertexArray->Bind();

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const Ref<Texture>& texture)
	{
		s_Data->DefaultShader->Bind();
		s_Data->QuadVertexArray->Bind();
		texture->Bind(0);

		s_Data->DefaultShader->SetMat4("u_MVP", s_Data->CameraBuffer->ViewProjection * glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1), scale));
		s_Data->DefaultShader->SetFloat4("u_Color", { 1.0, 1.0f, 1.0f, 1.0f });
		s_Data->DefaultShader->SetInt("u_Texture", 0);
		
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

    void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        s_Data->DefaultShader->Bind();
        s_Data->QuadVertexArray->Bind();

        s_Data->DefaultShader->SetMat4("u_MVP", s_Data->CameraBuffer->ViewProjection * transform);
        s_Data->DefaultShader->SetFloat4("u_Color", color);

        s_Data->DefaultTexture->Bind(0);
        s_Data->DefaultShader->SetInt("u_Texture", 0);

        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

}