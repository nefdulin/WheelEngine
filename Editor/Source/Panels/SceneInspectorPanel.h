#pragma once
#include "Wheel.h"

namespace Wheel {

    class SceneInspectorPanel
    {
    public:

        void OnImGuiRender();
        void DrawComponents(Entity& entity);

        void SetSelectedEntity(Entity& entity);
        void SetSelectedEntity(Entity* entity);
    private:
        Entity* m_SelectedEntity;
    };

}
