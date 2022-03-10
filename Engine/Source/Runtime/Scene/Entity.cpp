#include "Entity.h"

namespace Wheel {

    Entity::Entity(entt::entity handle, const std::string& name, Scene* scene)
        : m_Handle(handle), m_Name(name), m_Scene(scene)
    {
    }

    Entity::Entity(entt::entity handle, Scene *scene)
        : m_Handle(handle), m_Scene(scene)
    {
    }
}
