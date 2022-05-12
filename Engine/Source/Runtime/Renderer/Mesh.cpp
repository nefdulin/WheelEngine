#include "Mesh.h"

#define M_PI   3.14159265358979323846264338327950288

namespace Wheel {
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t> indices, const std::vector<Ref<Texture>>& textures) :
        m_Vertices(vertices), m_Indices(indices), m_Textures(textures)

    {
        SetupMesh();
    }

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) :
		m_Vertices(vertices), m_Indices(indices)
	{
		SetupMesh();
	}

    void Mesh::SetupMesh()
    {
        m_VertexArray = VertexArray::CreateVertexArray();

        m_VertexBuffer = VertexBuffer::CreateVertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
        m_IndexBuffer = IndexBuffer::CreateIndexBuffer(m_Indices.data(), m_Indices.size());

        BufferLayout layout{
            { ShaderDataType::Float3, "a_Position"},
            { ShaderDataType::Float3, "a_Normal"},
            { ShaderDataType::Float2, "a_TexCoords"},
            { ShaderDataType::Float3, "a_Tangent"},
            { ShaderDataType::Float3, "a_Bitangent"}
        };

		//BufferLayout layout{
		//	{ShaderDataType::Float3, "a_Positions"},
		//	{ShaderDataType::Float2, "a_TexCoords"}
		//};

        m_VertexBuffer->SetLayout(layout);

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
    }

    Ref<Mesh> MeshFactory::CreateCube(const glm::vec3& size)
    {
		std::vector<Vertex> vertices;
		vertices.resize(8);
		vertices[0].Position = { -size.x / 2.0f, -size.y / 2.0f,  size.z / 2.0f };
		vertices[1].Position = { size.x / 2.0f, -size.y / 2.0f,  size.z / 2.0f };
		vertices[2].Position = { size.x / 2.0f,  size.y / 2.0f,  size.z / 2.0f };
		vertices[3].Position = { -size.x / 2.0f,  size.y / 2.0f,  size.z / 2.0f };
		vertices[4].Position = { -size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f };
		vertices[5].Position = { size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f };
		vertices[6].Position = { size.x / 2.0f,  size.y / 2.0f, -size.z / 2.0f };
		vertices[7].Position = { -size.x / 2.0f,  size.y / 2.0f, -size.z / 2.0f };

		vertices[0].Normal = { -1.0f, -1.0f,  1.0f };
		vertices[1].Normal = { 1.0f, -1.0f,  1.0f };
		vertices[2].Normal = { 1.0f,  1.0f,  1.0f };
		vertices[3].Normal = { -1.0f,  1.0f,  1.0f };
		vertices[4].Normal = { -1.0f, -1.0f, -1.0f };
		vertices[5].Normal = { 1.0f, -1.0f, -1.0f };
		vertices[6].Normal = { 1.0f,  1.0f, -1.0f };
		vertices[7].Normal = { -1.0f,  1.0f, -1.0f };

		std::vector<Index> indexVector;
		indexVector.resize(12);
		indexVector[0] = { 0, 1, 2 };
		indexVector[1] = { 2, 3, 0 };
		indexVector[2] = { 1, 5, 6 };
		indexVector[3] = { 6, 2, 1 };
		indexVector[4] = { 7, 6, 5 };
		indexVector[5] = { 5, 4, 7 };
		indexVector[6] = { 4, 0, 3 };
		indexVector[7] = { 3, 7, 4 };
		indexVector[8] = { 4, 5, 1 };
		indexVector[9] = { 1, 0, 4 };
		indexVector[10] = { 3, 2, 6 };
		indexVector[11] = { 6, 7, 3 };

		std::vector<uint32_t> indices;
		indices.resize(36);

		for (int i = 0; i < 12; i++)
		{
			indices[(i * 3)] = indexVector[i].v1;
			indices[(i * 3) + 1] = indexVector[i].v2;
			indices[(i * 3) + 2] = indexVector[i].v3;
		}

        return CreateRef<Mesh>(vertices, indices);
    }

	Ref<Mesh> MeshFactory::CreateSphere(float radius)
	{
		std::vector<Vertex> vertices;
		std::vector<Index> indicesVector;

		constexpr float latitudeBands = 30;
		constexpr float longitudeBands = 30;

		for (float latitude = 0.0f; latitude <= latitudeBands; latitude++)
		{
			const float theta = latitude * (float)M_PI / latitudeBands;
			const float sinTheta = glm::sin(theta);
			const float cosTheta = glm::cos(theta);

			for (float longitude = 0.0f; longitude <= longitudeBands; longitude++)
			{
				const float phi = longitude * 2.f * (float)M_PI / longitudeBands;
				const float sinPhi = glm::sin(phi);
				const float cosPhi = glm::cos(phi);

				Vertex vertex;
				vertex.Normal = { cosPhi * sinTheta, cosTheta, sinPhi * sinTheta };
				vertex.Position = { radius * vertex.Normal.x, radius * vertex.Normal.y, radius * vertex.Normal.z };
				vertices.push_back(vertex);
			}
		}

		for (uint32_t latitude = 0; latitude < (uint32_t)latitudeBands; latitude++)
		{
			for (uint32_t longitude = 0; longitude < (uint32_t)longitudeBands; longitude++)
			{
				const uint32_t first = (latitude * ((uint32_t)longitudeBands + 1)) + longitude;
				const uint32_t second = first + (uint32_t)longitudeBands + 1;

				indicesVector.push_back({ first, second, first + 1 });
				indicesVector.push_back({ second, second + 1, first + 1 });
			}
		}

		std::vector<uint32_t> indices;
		indices.resize(indicesVector.size() * 3);
		for (int i = 0; i < indicesVector.size(); i++)
		{
			indices[(i * 3)] = indicesVector[i].v1;
			indices[(i * 3) + 1] = indicesVector[i].v2;
			indices[(i * 3) + 2] = indicesVector[i].v3;
		}

		return CreateRef<Mesh>(vertices, indices);
	}

}
