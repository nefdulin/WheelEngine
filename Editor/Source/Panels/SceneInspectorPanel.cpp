#include "SceneInspectorPanel.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>

namespace Wheel {

    void SceneInspectorPanel::OnImGuiRender()
    {
        ImGui::Begin("Inspector");

        if (m_SelectedEntity)
            DrawComponents(*m_SelectedEntity);

        ImGui::End();
    }

    void SceneInspectorPanel::DrawComponents(Entity& entity)
    {
        auto& name = entity.GetName();

        char buffer[256];
        memset(buffer, 0, sizeof(buffer));
        strcpy(buffer, name.c_str());
        if (ImGui::InputText("Name", buffer, sizeof(buffer)))
        {
            name = std::string(buffer);
        }

        if (entity.HasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                auto& transform = entity.GetComponent<TransformComponent>();
                ImGui::DragFloat3("Position", glm::value_ptr(transform.Position), 0.1f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(transform.Rotation), 0.1f);
                ImGui::DragFloat3("Scale", glm::value_ptr(transform.Scale), 0.1f);
                ImGui::TreePop();
            }
        }
    }

    void SceneInspectorPanel::SetSelectedEntity(Entity& entity)
    {
        m_SelectedEntity = &entity;
    }
}
