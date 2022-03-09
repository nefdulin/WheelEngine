#pragma once
#include "Renderer/Camera.h"

namespace Wheel {

    // TODO: Divide this class into two different classes
    // TODO: SceneOrthographicCamera and ScenePerspectiveCamera
    class SceneCamera : public Camera
    {
    public:
        SceneCamera() = default;
        virtual ~SceneCamera() = default;

        void SetOrthographicSize(float size, float nearClip, float farClip);
        void SetViewportSize(uint32_t width, uint32_t height);
    private:
        void RecalculateOrthographicProjection();
    private:
        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

        float m_AspectRatio = 0.0f;
    };

}
