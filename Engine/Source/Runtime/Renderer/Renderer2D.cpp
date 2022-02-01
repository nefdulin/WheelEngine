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
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // top left 
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

	void Renderer2D::DrawQuad(glm::vec2 position, glm::vec2 color)
	{

	}

	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec3 scale)
	{
		s_Data->DefaultShader->Bind();
		s_Data->QuadVertexArray->Bind();

		s_Data->DefaultShader->SetMat4("u_MVP", s_Data->CameraBuffer->ViewProjection * glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1), scale));

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec3 scale, const Ref<Texture>& texture)
	{
		s_Data->DefaultShader->Bind();
		s_Data->QuadVertexArray->Bind();
		texture->Bind(0);

		s_Data->DefaultShader->SetMat4("u_MVP", s_Data->CameraBuffer->ViewProjection * glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1), scale));
		s_Data->DefaultShader->SetInt("u_Texture", 0);
		
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}