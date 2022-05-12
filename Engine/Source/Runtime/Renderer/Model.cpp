#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Wheel {

	Model::Model(const std::string& path)
	{
		m_Path = path;
		int lastPos = path.find_last_of("/");
		m_Name = path.substr(lastPos + 1, path.npos);
		Load(path);
	}

	void Model::Load(const std::string& path)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			WHEEL_CORE_ASSERT(false, "Error with importing asset at path: {0}", path.c_str());
			return;
		}

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Ref<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<Ref<Texture>> textures; 

		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			vertex.Position.x = mesh->mVertices[i].x;
			vertex.Position.y = mesh->mVertices[i].y;
			vertex.Position.z = mesh->mVertices[i].z;

			if (mesh->HasNormals())
			{
				vertex.Normal.x = mesh->mNormals[i].x;
				vertex.Normal.y = mesh->mNormals[i].y;
				vertex.Normal.z = mesh->mNormals[i].z;
			}

			if (mesh->mTextureCoords[0])
			{
				vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;

				vertex.Tangent.x = mesh->mTangents[i].x;
				vertex.Tangent.y = mesh->mTangents[i].y;
				vertex.Tangent.z = mesh->mTangents[i].z;

				vertex.Bitangent.x = mesh->mBitangents[i].x;
				vertex.Bitangent.y = mesh->mBitangents[i].y;
				vertex.Bitangent.z = mesh->mBitangents[i].z;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		textures = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);

		return CreateRef<Mesh>(vertices, indices, textures);
	}

	std::vector<Ref<Texture>> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType aiType, TextureType type)
	{
		std::vector<Ref<Texture>> textures;

		for (int i = 0; i < material->GetTextureCount(aiType); i++)
		{
			aiString str;
			material->GetTexture(aiType, i, &str);
			bool skip = false;
			std::string path = std::string("assets/models/") + str.C_Str();
			for (int i = 0; i < m_LoadedTextures.size(); i++)
			{
				if (m_LoadedTextures[i]->GetPath() == path.c_str())
				{
					skip = true;
					textures.push_back(m_LoadedTextures[i]);
					break;
				}
			}

			if (!skip)
			{
				Ref<Texture2D> texture = Texture2D::Create(path, type);
				textures.push_back(texture);
				m_LoadedTextures.push_back(texture);
			}
		}

		return textures;
	}

}