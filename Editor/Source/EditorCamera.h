#pragma once
#include <Renderer/Camera.h>

namespace Wheel
{
    // Currently, only support perspective camera
    class EditorCamera : public Camera
    {
    public:
        EditorCamera() = default;

        EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

        virtual ~EditorCamera() override;

        inline void SetViewportSize(uint32_t width, uint32_t height) { m_ViewportWidth = width; m_ViewportHeight = height; CalculateProjectionMatrix(); }

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& newPosition) { m_Position = newPosition; }

        void OnUpdate(float deltaTime);

        void Rotate(const glm::vec2& delta);

        glm::quat GetOrientation() const;

        glm::vec3 GetUpDirection() const;
        glm::vec3 GetForwardDirection() const;
        glm::vec3 GetRightDirection() const;

    private:
        void CalculateProjectionMatrix();
        void CalculateViewMatrix();
    private:
        glm::vec3 m_Position { 0.0f, 0.0f, 10.0f };

        glm::vec2 m_LastMousePosition = {};

        float m_Yaw = 0, m_Pitch = 0;

        float m_CameraSpeed = 50.0f, m_RotationSpeed = 0.8f;

        float m_ViewportWidth = 1280, m_ViewportHeight = 720;

        float m_FOV = 45.0f, m_AspectRatio = 1.6f, m_NearClip = 0.01f, m_FarClip = 10000.0f;

    };
}
