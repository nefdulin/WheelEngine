#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "SceneCamera.h"

namespace Wheel {

    struct TransformComponent
    {
        TransformComponent() = default;
        TransformComponent(const TransformComponent& other) = default;
        TransformComponent(const glm::vec3& position) :
            Position(position) {}

        operator glm::mat4() { return GetTransform(); }

        glm::mat4 GetTransform() const
        {
            return glm::translate(glm::mat4(1.0f), Position)
                * glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(0.0f, 0.0f, 1.0f))
                * glm::scale(glm::mat4(1.0f), Scale);
        }

        glm::vec3 Position  = {0.0f, 0.0f, 0.0f};
        glm::vec3 Rotation  = {0.0f, 0.0f, 0.0f};
        glm::vec3 Scale     = {1.0f, 1.0f, 1.0f};
    };

    struct SpriteRendererComponent
    {
        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent& other) = default;
        SpriteRendererComponent(const glm::vec4& color) :
            Color(color) {}

        operator glm::vec4() { return Color; }
        glm::vec4 Color{1.0f};
    };

    struct CameraComponent
    {
        CameraComponent() = default;
        CameraComponent(const CameraComponent& other) = default;

        SceneCamera Camera;
    };

}
