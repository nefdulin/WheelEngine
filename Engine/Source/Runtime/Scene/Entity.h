#pragma once
#include "Scene.h"

namespace Wheel
{
    class Entity
    {
    public:
        Entity() = default;

        Entity(entt::entity handle, Scene *scene);

        Entity(entt::entity handle, const std::string &name, Scene *scene);

        Entity(const Entity &other) = default;

        template<typename T, typename... Args>
        T &AddComponent(Args &&... args)
        {
            WHEEL_CORE_ASSERT(!HasComponent<T>(), "Component already exists!");
            return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
        }

        template<typename T>
        T &GetComponent()
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

        const std::string& GetName() const { return m_Name; }
        std::string& GetName() { return m_Name; }

        const entt::entity& GetHandle() const { return m_Handle; }

        operator uint32_t() const { return (uint32_t) m_Handle; }
        bool operator==(const Entity& other) const { return m_Handle == other.m_Handle && m_Scene == other.m_Scene; }

    private:
        entt::entity m_Handle {entt::null};
        std::string m_Name {"Entity"};
        Scene* m_Scene {nullptr};
    };
}