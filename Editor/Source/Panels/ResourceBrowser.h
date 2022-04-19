#pragma once
#include <filesystem>
#include <Wheel.h>

namespace Wheel
{
	class ResourceBrowser
	{
	public:
		ResourceBrowser();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;
		Ref<Texture2D> m_DirectoryImage;
		Ref<Texture2D> m_FileImage;
	};
}

