#pragma once
#include "Wheel.h"

namespace Wheel {

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel(const Ref<Scene>& context);

        void SetContext(const Ref<Scene>& context);
        Entity& GetSelectedEntity();

        void OnImGuiRender();
    private:
        void DrawEntityNode(Entity& entity);
    private:
        Ref<Scene> m_Context;
        Entity* m_SelectedEntity;
    };

}