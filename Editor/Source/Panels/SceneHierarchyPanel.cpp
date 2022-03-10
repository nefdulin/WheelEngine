#include "SceneHierarchyPanel.h"
#include <imgui.h>

namespace Wheel {

    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene> &context)
    {
        SetContext(context);
    }

    void SceneHierarchyPanel::SetContext(const Ref<Scene> &context)
    {
        m_Context = context;
    }

    Entity& SceneHierarchyPanel::GetSelectedEntity()
    {
        return *m_SelectedEntity;
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Hierarchy");

        m_Context->m_Registry.each([&](auto handle)
        {
            DrawEntityNode(m_Context->GetEntityFromEntityHandle(handle));
        });

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            m_SelectedEntity = nullptr;

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity& entity)
    {
        ImGuiTreeNodeFlags flags = ((m_SelectedEntity != nullptr && *m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0 )
                | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t) entity, flags, entity.GetName().c_str());

        if (ImGui::IsItemClicked())
            m_SelectedEntity = &entity;

        if (opened)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

            opened = ImGui::TreeNodeEx((void*) 6534635, flags, entity.GetName().c_str());
            if (opened)
                ImGui::TreePop();

            ImGui::TreePop();
        }
    }
}
