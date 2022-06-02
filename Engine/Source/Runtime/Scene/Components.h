#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include "Renderer/Model.h"

namespace Wheel {

    struct TransformComponent
    {
        TransformComponent() = default;
        TransformComponent(const TransformComponent& other) = default;
        TransformComponent(const glm::vec3& position)
            :   Position(position) {}

        operator glm::mat4() { return GetTransform(); }

        glm::mat4 GetTransform() const
        {
            glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

            return glm::translate(glm::mat4(1.0f), Position)
                   * rotation * glm::scale(glm::mat4(1.0f), Scale);
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

    struct ModelRendererComponent
    {
        ModelRendererComponent() = default;
        ModelRendererComponent(const ModelRendererComponent& other) = default;
        ModelRendererComponent(const std::string& path)
        {
            model = CreateRef<Model>(path);
        }

        operator const Ref<Model>() const { return model; }

        // Fix this
        Ref<Model> model; 
    };

    struct MeshRendererComponent
    {
        MeshRendererComponent() = default;
        MeshRendererComponent(const MeshRendererComponent& other) = default;
        
        //operator Ref<Mesh>() { return Mesh; }
        operator Ref<Mesh>() { return Mesh; }

        Ref<Mesh> Mesh;

        glm::vec4 Color{ 1.0f };
    };

    struct CameraComponent
    {
        CameraComponent() = default;
        CameraComponent(const CameraComponent& other) = default;

        SceneCamera Camera;
    };

    struct NativeScriptComponent
    {
        ScriptableEntity*(*InstantiateScript)(Entity& entity);
        void (*DestroyScript)(NativeScriptComponent*);

        template<typename T>
        void Bind()
        {
            InstantiateScript = [](Entity& e)
            {
                auto scriptableEntity = static_cast<ScriptableEntity*>(new T());
                scriptableEntity->SetEntity(e);
                return scriptableEntity;
            };

            DestroyScript = [](NativeScriptComponent* component) { delete component->Instance; component->Instance = nullptr; };
        }

        ScriptableEntity* Instance = nullptr;
    };

}
