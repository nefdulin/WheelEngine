#pragma once
#include "Core/Core.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>

namespace Wheel {

	class Camera
	{
	public:
		Camera() = default;
        Camera(const glm::mat4& proj)
            : m_ProjectionMatrix(proj) {}

		virtual ~Camera() = default;

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

        // TODO: Add ViewMatrix as well
	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	};

}
