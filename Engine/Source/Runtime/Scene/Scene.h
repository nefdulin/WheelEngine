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
    private:
        entt::registry  m_Registry;
    };

}