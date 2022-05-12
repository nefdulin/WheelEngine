#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Wheel {

	class Model
	{
	public:
		Model() = default;
		Model(const std::string& path);

		const std::vector<Ref<Mesh>>& GetMeshes() const { return m_Meshes; }
		const std::string& GetName() const { return m_Name; }

	private:
		void Load(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		std::vector<Ref<Texture>> LoadMaterialTextures(aiMaterial* material, aiTextureType aiType, TextureType type);
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		std::vector<Ref<Mesh>> m_Meshes;
		std::vector<Ref<Texture>> m_LoadedTextures;
		std::string m_Name;
		std::string m_Path;
	};

}