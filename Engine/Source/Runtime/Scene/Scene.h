#pragma once
#include <entt/entt.hpp>

namespace Wheel {

    class Entity;

    class Scene
    {
        friend class Entity;
    public:
        Scene();

        Entity CreateEntity(const std::string& name);
        void OnUpdate(float deltaTime);

        void OnViewportResize(uint32_t width, uint32_t height);
    private:
        entt::registry  m_Registry;
        // TODO: map all the entities that are active in the scene
        std::unordered_map<entt::entity, Entity> m_EntityMap;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
    };

}