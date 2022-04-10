#include "EditorCamera.h"
#include <glm/gtx/quaternion.hpp>
#include <Core/Input.h>
#include <Core/KeyCodes.h>
#include <Core/MouseCodes.h>
#include <Core/Log.h>

namespace Wheel {

    EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
            : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip), Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
    {
        m_LastMousePosition = Input::GetMousePosition();
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
        glm::quat orientation = GetOrientation();
        m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
        m_ViewMatrix = glm::inverse(m_ViewMatrix);
    }

    void EditorCamera::OnUpdate(float deltaTime)
    {
        glm::vec2 mousePos = Input::GetMousePosition();

        if (Input::IsMousePressed(Mouse::ButtonRight))
        {
            glm::vec2 delta = (mousePos - m_LastMousePosition) * 0.003f;

            glm::vec3 newPosition = m_Position;
            if (Input::IsKeyPressed(Key::W))
                newPosition += GetForwardDirection() * deltaTime * m_CameraSpeed;
            else if (Input::IsKeyPressed(Key::S))
                newPosition -= GetForwardDirection() * deltaTime * m_CameraSpeed;

            if (Input::IsKeyPressed(Key::D))
                newPosition += GetRightDirection() * deltaTime * m_CameraSpeed;
            else if (Input::IsKeyPressed(Key::A))
                newPosition -= GetRightDirection() * deltaTime * m_CameraSpeed;

            m_Position = newPosition;

            Rotate(delta);
        }

        CalculateViewMatrix();
        //CalculateProjectionMatrix();

        m_LastMousePosition = mousePos;
    }

    void EditorCamera::Rotate(const glm::vec2& delta)
    {
        float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
        m_Yaw += yawSign * delta.x * m_RotationSpeed;
        m_Pitch += delta.y * m_RotationSpeed;
    }

    glm::vec3 EditorCamera::GetUpDirection() const
    {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 EditorCamera::GetRightDirection() const
    {
        return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glm::vec3 EditorCamera::GetForwardDirection() const
    {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
    }

    glm::quat EditorCamera::GetOrientation() const
    {
        return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
    }

}

