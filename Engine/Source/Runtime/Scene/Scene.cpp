#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Renderer/Renderer2D.h"

namespace Wheel {

    Scene::Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        entt::entity handle = m_Registry.create();
        Entity entity = { handle, name, this };

        entity.AddComponent<TransformComponent>();
        return entity;
    }

    void Scene::OnUpdate(float deltaTime)
    {
        // TODO: Move this to Scene::OnScenePlayStart
        {
            m_Registry.view<NativeScriptComponent>().each([=](auto entity, NativeScriptComponent& component)
            {
                if (!component.Instance)
                {
                    component.Instance = component.InstantiateScript();
                    // TODO: Make m_Entity a pointer, hold all the entities inside a map
                    component.Instance->m_Entity = Entity{entity, this};
                    component.Instance->OnCreate();
                }

                component.Instance->OnUpdate(deltaTime);
            });
        }

        Camera* mainCamera = nullptr;
        glm::mat4 cameraTransform;
        {
            auto view = m_Registry.view<TransformComponent, CameraComponent>();
            for (auto entity : view)
            {
                auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                mainCamera = &camera.Camera;
                cameraTransform = transform.GetTransform();
            }
        }


        Wheel::Renderer2D::BeginScene(*mainCamera, cameraTransform);
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer2D::DrawQuad(transform, sprite);
        }

        Wheel::Renderer2D::EndScene();
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& camera = view.get<CameraComponent>(entity);

            camera.Camera.SetViewportSize(width, height);
        }
    }
}

