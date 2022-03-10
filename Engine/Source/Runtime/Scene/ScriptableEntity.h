#pragma once
#include "Entity.h"

namespace Wheel {

    class ScriptableEntity
    {
        friend class Scene;
    public:
        virtual ~ScriptableEntity() {}

        template <typename T>
        T& GetComponent()
        {
            WHEEL_CORE_ASSERT(m_Entity, "Trying to access an Entity that has been deleted!");
            return m_Entity->GetComponent<T>();
        }

        void SetEntity(Entity& entity) { m_Entity = &entity; }
    protected:
        virtual void OnCreate() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnDestroy() {}
    private:
        Entity* m_Entity;
    };

}
