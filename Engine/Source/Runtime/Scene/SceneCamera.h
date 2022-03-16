#pragma once
#include "Renderer/Camera.h"

namespace Wheel {

    // TODO: Divide this class into two different classes
    // TODO: SceneOrthographicCamera and ScenePerspectiveCamera
    class SceneCamera : public Camera
    {
    public:
        enum class ProjectionType
        {
            Perspective = 0,
            Orthographic = 1
        };
    public:
        SceneCamera() = default;

        SceneCamera(ProjectionType type)
            : m_ProjectionType(type) {}

        virtual ~SceneCamera() = default;


        void SetViewportSize(uint32_t width, uint32_t height);

        ProjectionType GetProjectionType() { return m_ProjectionType; }
        void SetProjectionType(ProjectionType type) { m_ProjectionType = type; RecalculateProjection(); };

        void SetPerspective(float fov, float nearClip, float farClip);

        float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
        void SetPerspectiveVerticalFOV(float fov) { m_PerspectiveFOV = fov; RecalculateProjection(); }

        float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
        void SetPerspectiveNearClip(float near) { m_PerspectiveNear = near; }

        float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
        void SetPerspectiveFarClip(float far) { m_PerspectiveFar = far; RecalculateProjection(); }

        void SetOrthographic(float size, float nearClip, float farClip);

        float GetOrthographicSize() const { return m_OrthographicSize; }
        void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }

        float GetOrthographicNearClip() const { return m_OrthographicNear; }
        void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; RecalculateProjection(); }

        float GetOrthographicFarClip() const { return m_OrthographicFar; }
        void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; RecalculateProjection(); }

    private:
        void RecalculateProjection();
    private:
        ProjectionType m_ProjectionType = ProjectionType::Orthographic;

        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

        float m_PerspectiveFOV = glm::radians(45.0f);
        float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

        float m_AspectRatio = 0.0f;
    };

}
