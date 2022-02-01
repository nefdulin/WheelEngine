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

		static void DrawQuad(glm::vec2 position, glm::vec2 scale);
		static void DrawQuad(glm::vec3 position, glm::vec3 scale);
		static void DrawQuad(glm::vec3 position, glm::vec3 scale, const Ref<Texture>& texture);
	};

}
