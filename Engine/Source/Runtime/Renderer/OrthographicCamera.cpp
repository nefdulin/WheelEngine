#include "OrthographicCamera.h"
#include "Events/Event.h"

namespace Wheel {

	/*void OrthographicCamera::CalculateViewProjectionMatrix()
	{
		m_ViewMatrix = glm::translate(glm::mat4(1), m_Position) *
			glm::rotate(glm::mat4(1), glm::radians(m_Rotation.x), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1), glm::vec3(1.0f));

		m_ViewMatrix = glm::inverse(m_ViewMatrix);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}*/
}