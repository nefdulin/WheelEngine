#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "Buffer.h"
#include "Texture.h"

namespace Wheel {

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	struct Index
	{
		uint32_t v1, v2, v3;
	};

	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t> indices, const std::vector<Ref<Texture>>& textures);

		const std::vector<Ref<Texture>>& GetTextures() const { return m_Textures; }
		const Ref<VertexArray>& GetVertexArray() const { return m_VertexArray; }

	private:
		void SetupMesh();

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;
		std::vector<Ref<Texture>> m_Textures;
	};

	class MeshFactory
	{
	public:
		static Ref<Mesh> CreateCube(const glm::vec3& scale);
		static Ref<Mesh> CreateSphere(float radius);
	};
}

