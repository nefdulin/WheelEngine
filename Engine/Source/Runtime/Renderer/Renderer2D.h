#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"

namespace Wheel {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Ref<Camera>& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& scale);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const Ref<Texture>& texture);

        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	};

}
