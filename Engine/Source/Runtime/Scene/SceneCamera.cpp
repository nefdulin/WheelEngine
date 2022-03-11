#include "SceneCamera.h"

namespace Wheel {

    void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
    {
        m_ProjectionType = ProjectionType::Perspective;
        m_PerspectiveFOV = verticalFOV;
        m_PerspectiveNear = nearClip;
        m_PerspectiveFar = farClip;
        RecalculateProjection();
    }

    void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
    {
        m_ProjectionType = ProjectionType::Orthographic;
        m_OrthographicSize = size;
        m_OrthographicNear = nearClip;
        m_OrthographicFar = farClip;
        RecalculateProjection();
    }

    void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
    {
        m_AspectRatio = (float) width / (float) height;
        RecalculateProjection();
    }

    void SceneCamera::RecalculateProjection()
    {
        switch (m_ProjectionType)
        {
            case ProjectionType::Perspective:
            {
                m_ProjectionMatrix = glm::perspective(glm::radians(m_PerspectiveFOV), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
            }break;
            case ProjectionType::Orthographic:
            {
                float left = -m_OrthographicSize * m_AspectRatio * 0.5f;
                float right = m_OrthographicSize * m_AspectRatio * 0.5f;
                float bottom = -m_OrthographicSize * 0.5f;
                float top = m_OrthographicSize * 0.5f;

                m_ProjectionMatrix = glm::ortho(left, right, bottom, top, m_OrthographicNear, m_OrthographicFar);
            }break;
        }
    }

}