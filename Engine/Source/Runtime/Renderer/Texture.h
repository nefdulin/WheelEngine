#pragma once

namespace Wheel {

	enum class TextureType
	{
		DIFFUSE = 0, 
		SPECULAR,
		NORMAL,
		HEIGHT
	};

	static std::string TextureTypeToName(TextureType type)
	{
		switch (type)
		{
			case TextureType::DIFFUSE:
				return "diffuse";
			case TextureType::SPECULAR:
				return "specular";
			case TextureType::NORMAL:
				return "normal";
			case TextureType::HEIGHT:
				return "height";
		}
	}

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;
		virtual TextureType GetType() const = 0;
		virtual std::string GetPath() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create(const std::string& path, TextureType type);
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
	};
}