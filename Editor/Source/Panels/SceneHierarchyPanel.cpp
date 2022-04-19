#include "SceneHierarchyPanel.h"
#include <imgui.h>

namespace Wheel {

    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene> &context) : 
        m_SelectedEntity(nullptr)
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

        // Right-click on blank space
        if (ImGui::BeginPopupContextWindow(0, 1, false))
        {
            if (ImGui::MenuItem("Create Empty Entity"))
                m_Context->CreateEntity("Empty Entity");

            ImGui::EndPopup();
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity& entity)
    {
        ImGuiTreeNodeFlags flags;
        if (m_SelectedEntity != nullptr)
            flags = (*m_SelectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0 ) | ImGuiTreeNodeFlags_OpenOnArrow;

        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t) entity, flags, entity.GetName().c_str());

        if (ImGui::IsItemClicked())
            m_SelectedEntity = &entity;

        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete Entity"))
                entityDeleted = true;

            ImGui::EndPopup();
        }

        if (opened)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

            opened = ImGui::TreeNodeEx((void*) 6534635, flags, entity.GetName().c_str());
            if (opened)
                ImGui::TreePop();

            ImGui::TreePop();
        }

        if (entityDeleted)
        {
            m_Context->DestroyEntity(entity);
            if (*m_SelectedEntity == entity)
                m_SelectedEntity = nullptr;
        }
    }
}
