#pragma once
#include "Core/Core.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>

namespace Wheel {

    // TODO: turn this to a complete interface
	class Camera
	{
    public:
        enum class ProjectionType
        {
            Perspective = 0,
            Orthographic = 1
        };
	public:
		Camera() = default;
        Camera(const glm::mat4& proj)
            : m_ProjectionMatrix(proj) {}

		virtual ~Camera() = default;

		virtual const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

        // TODO: Add ViewMatrix as well
	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewMatrix;
	};

}
