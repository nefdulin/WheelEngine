#include "ResourceBrowser.h"
#include <imgui.h>

namespace Wheel
{
	const static std::filesystem::path s_DefaultPath = "assets";

	const static int s_IconSize = 64;

	ResourceBrowser::ResourceBrowser()
		: m_CurrentDirectory(s_DefaultPath)
	{
		m_DirectoryImage = Texture2D::Create("resources/icons/directory.png");
		m_FileImage = Texture2D::Create("resources/icons/file.png");
	}

	void ResourceBrowser::OnImGuiRender()
	{
		ImGui::Begin("Resource Browser");

		if (m_CurrentDirectory != s_DefaultPath)
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		uint8_t columnCount = ImGui::GetContentRegionAvail().x / s_IconSize;

        if (columnCount <= 0)
            return;

		if (ImGui::BeginTable(m_CurrentDirectory.string().c_str(), columnCount))
		{
			for (auto& directory : std::filesystem::directory_iterator(m_CurrentDirectory))
			{
				ImGui::TableNextColumn();
				auto path = directory.path();
				auto relativePath = std::filesystem::relative(path, s_DefaultPath);
				std::string filenameString = relativePath.filename().string();

				ImGui::PushID(filenameString.c_str());

				if (directory.is_directory())
				{
					ImGui::ImageButton((ImTextureID)m_DirectoryImage->GetRendererID(), { s_IconSize, s_IconSize }, { 0, 1 }, { 1, 0 });

					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					{
						m_CurrentDirectory /= relativePath.filename();
					}

					ImGui::TextWrapped(filenameString.c_str());
				}
				else
				{
					if (ImGui::ImageButton((ImTextureID)m_FileImage->GetRendererID(), { s_IconSize, s_IconSize }, { 0, 1 }, { 1, 0 }))
					{
						// Open file type related window
					}
					ImGui::TextWrapped(filenameString.c_str());
				}

				ImGui::PopID();
			}

			ImGui::EndTable();
		}

		ImGui::End();
	}
}