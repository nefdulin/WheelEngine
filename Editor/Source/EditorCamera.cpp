#include "EditorCamera.h"
#include <glm/gtx/quaternion.hpp>
#include <Core/Input.h>

namespace Wheel {

    EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
            : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip), Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
    {
        CalculateViewMatrix();
    }

    EditorCamera::~EditorCamera()
    {

    }

    void EditorCamera::CalculateProjectionMatrix()
    {
        m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
    }

    void EditorCamera::CalculateViewMatrix()
    {
        m_ViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void EditorCamera::OnUpdate(float deltaTime)
    {
        CalculateViewMatrix();
        CalculateProjectionMatrix();
    }


}

