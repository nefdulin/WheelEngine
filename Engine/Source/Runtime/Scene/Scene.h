#pragma once
#include <entt/entt.hpp>

namespace Wheel {

    class Entity;

    class Scene
    {
        friend class SceneHierarchyPanel;
        friend class Entity;
    public:
        Scene();

        Ref<Entity> CreateEntity(const std::string& name);
        void OnUpdate(float deltaTime);

        Entity& GetEntityFromEntityHandle(entt::entity handle);

        void OnViewportResize(uint32_t width, uint32_t height);
    private:
        entt::registry  m_Registry;
        // TODO: map all the entities that are active in the scene
        std::unordered_map<entt::entity, Ref<Entity>> m_EntityMap;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
    };

}