#pragma once
#include <Renderer/Camera.h>

namespace Wheel
{
    class EditorCamera : public Camera
    {
    public:
        EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

        virtual ~EditorCamera();
    private:
        glm::mat4 m_ViewMatrix{1.0f};

        float m_Fov = 45.0f;
    };
}
