#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Camera.h"
#include "unordered_map"
#include "Renderer/Renderer.h"

namespace Wheel {

    Scene::Scene()
    {
    }

    Ref<Entity> Scene::CreateEntity(const std::string& name)
    {
        entt::entity handle = m_Registry.create();
        Ref<Entity> entity = CreateRef<Entity>(handle, name, this);
        m_EntityMap.emplace(std::make_pair(handle, entity));

        entity->AddComponent<TransformComponent>();
        return entity;
    }

    void Scene::DestroyEntity(Entity& entity)
    {
        m_Registry.destroy(entity.GetHandle());
        m_EntityMap.erase(entity.GetHandle());
    }

    Entity& Scene::GetEntityFromEntityHandle(entt::entity handle)
    {
        WHEEL_CORE_ASSERT(m_EntityMap.find(handle) != m_EntityMap.end(), "Can't find entity inside entity map");
        return *(m_EntityMap.find(handle)->second);
    }

    void Scene::OnUpdate(float deltaTime)
    {
        // TODO: Move this to Scene::OnScenePlayStart
        {
            m_Registry.view<NativeScriptComponent>().each([=](auto handle, NativeScriptComponent& component)
            {
                if (!component.Instance)
                {
                    component.Instance = component.InstantiateScript(GetEntityFromEntityHandle(handle));
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

        Renderer::BeginScene(*mainCamera, cameraTransform);
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer::DrawQuad(transform, sprite);
        }

        Renderer::EndScene();
    }

    void Scene::OnUpdateEditor(float deltaTime, const Camera& c)
    {
        Renderer::BeginScene(c.GetProjectionMatrix() * c.GetViewMatrix());

        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer::DrawQuad(transform, sprite);
        }

        Renderer::EndScene();
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

