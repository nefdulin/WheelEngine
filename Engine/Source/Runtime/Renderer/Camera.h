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

		Camera(const glm::mat4 projection) : 
			m_ProjectionMatrix(projection)
		{}

		virtual ~Camera() = default;

		void OnUpdate() { CalculateViewProjectionMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		virtual void SetPosition(glm::vec3& position) { m_Position = position; }
		virtual const glm::vec3& GetPosition() const { return m_Position; }

		virtual void SetRotation(glm::vec3& rotation) { m_Rotation = rotation; }
		virtual const glm::vec3 GetRotation(glm::vec3& rotation) { return m_Rotation; }

		virtual void CalculateViewProjectionMatrix() = 0;

	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1);
		glm::mat4 m_ViewMatrix = glm::mat4(1);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1);

		glm::vec3 m_Position = glm::vec3(1.0f);
		glm::vec3 m_Rotation = glm::vec3(1.0f);
	};

}