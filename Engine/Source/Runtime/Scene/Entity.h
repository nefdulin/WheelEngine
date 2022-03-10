#pragma once
#include "Scene.h"

namespace Wheel
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(entt::entity handle, const std::string& name, Scene* scene);
        Entity(const Entity& other) = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            WHEEL_CORE_ASSERT(!HasComponent<T>(), "Component already exists!");
            return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent()
        {
            WHEEL_CORE_ASSERT(HasComponent<T>(), "Component does not exists!");
            return m_Scene->m_Registry.get<T>(m_Handle);
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Scene->m_Registry.all_of<T>(m_Handle);
        }

        template<typename T>
        void RemoveComponent()
        {
            WHEEL_CORE_ASSERT(HasComponent<T>(), "Component does not exists!");
            m_Scene->m_Registry.remove<T>(m_Handle);
        }
    private:
        entt::entity m_Handle {entt::null};
        std::string m_Name {"Entity"};
        Scene* m_Scene {nullptr};
    };
}