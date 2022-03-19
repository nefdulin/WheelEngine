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
    private:
        void CalculateProjectionMatrix();
        void CalculateViewMatrix();
    private:
        glm::vec3 m_Position { 1.0f };
        glm::vec3 m_Rotation { 1.0f };

        float m_ViewportWidth = 1280;
        float m_ViewportHeight = 720;

        float m_FOV = 45.0f;
        float m_AspectRatio = 1.6f;
        float m_NearClip = 0.01f;
        float m_FarClip = 10000.0f;
    };
}
