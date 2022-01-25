#pragma once
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Wheel {

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top)
		{
			m_ProjectionMatrix = glm::ortho(left, right, bottom, top);

			CalculateViewProjectionMatrix();
		}

		void CalculateViewProjectionMatrix() override;
	};

}
