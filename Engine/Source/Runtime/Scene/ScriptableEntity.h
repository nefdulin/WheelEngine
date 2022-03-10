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
            return m_Entity.GetComponent<T>();
        }
    protected:
        virtual void OnCreate() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnDestroy() {}
    private:
        Entity m_Entity;
    };

}
