#include "SceneCamera.h"

namespace Wheel {

    void SceneCamera::SetOrthographicSize(float size, float nearClip, float farClip)
    {
        m_OrthographicSize = size;
        m_OrthographicNear = nearClip;
        m_OrthographicFar = farClip;

        RecalculateOrthographicProjection();
    }

    void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
    {
        m_AspectRatio = (float) width / (float) height;
        RecalculateOrthographicProjection();
    }

    void SceneCamera::RecalculateOrthographicProjection()
    {
        float left = -m_OrthographicSize * m_AspectRatio * 0.5f;
        float right = m_OrthographicSize * m_AspectRatio * 0.5f;
        float bottom = -m_OrthographicSize * 0.5f;
        float top = m_OrthographicSize * 0.5f;

        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, m_OrthographicNear, m_OrthographicFar);
    }

}