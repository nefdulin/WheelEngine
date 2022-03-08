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
        Entity entity = { m_Registry.create(), name, this };

        entity.AddComponent<TransformComponent>();
        return entity;
    }

    void Scene::OnUpdate(float deltaTime)
    {
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer2D::DrawQuad(transform, sprite);
        }
    }
}

