#include "SceneInspectorPanel.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>

namespace Wheel {

    template<typename T, typename UIFunction>
    static void DrawComponent(const std::string& name, Entity& entity, UIFunction uiFunction)
    {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
        if (entity.HasComponent<T>())
        {
            auto& component = entity.GetComponent<T>();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();
            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
            ImGui::PopStyleVar(
            );
            ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
            if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
            {
                ImGui::OpenPopup("ComponentSettings");
            }

            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove component"))
                    removeComponent = true;

                ImGui::EndPopup();
            }

            if (open)
            {
                uiFunction(component);
                ImGui::TreePop();
            }

            if (removeComponent)
                entity.RemoveComponent<T>();
        }
    }

    static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

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
        if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
        {
            name = std::string(buffer);
        }

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");

        if (ImGui::BeginPopup("AddComponent"))
        {
            if (ImGui::MenuItem("Camera"))
            {
                m_SelectedEntity->AddComponent<CameraComponent>();
                ImGui::CloseCurrentPopup();
            }

            if (!entity.HasComponent<SpriteRendererComponent>() && ImGui::MenuItem("Sprite Renderer"))
            {
                m_SelectedEntity->AddComponent<SpriteRendererComponent>();
                ImGui::CloseCurrentPopup();
            }


            if (!entity.HasComponent<MeshRendererComponent>() && ImGui::MenuItem("Mesh Renderer"))
            {
                m_SelectedEntity->AddComponent<MeshRendererComponent>();
                ImGui::CloseCurrentPopup();
            }

            if (!entity.HasComponent<ModelRendererComponent>() && ImGui::MenuItem("Model Renderer"))
            {
                m_SelectedEntity->AddComponent<ModelRendererComponent>("assets/models/backpack/backpack.obj");
                ImGui::CloseCurrentPopup();
            }


            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();

        DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
        {
            DrawVec3Control("Translation", component.Position);
            glm::vec3 rotation = glm::degrees(component.Rotation);
            DrawVec3Control("Rotation", rotation);
            component.Rotation = glm::radians(rotation);
            DrawVec3Control("Scale", component.Scale, 1.0f);
        });

        DrawComponent<CameraComponent>("Camera", entity, [](auto& component)
        {
            auto& camera = component.Camera;

            const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
            const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
            if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
            {
                for (int i = 0; i < 2; i++)
                {
                    bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                    if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
                    {
                        currentProjectionTypeString = projectionTypeStrings[i];
                        camera.SetProjectionType((Camera::ProjectionType)i);
                    }

                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            if (camera.GetProjectionType() == Camera::ProjectionType::Perspective)
            {
                float perspectiveVerticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
                if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
                    camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));

                float perspectiveNear = camera.GetPerspectiveNearClip();
                if (ImGui::DragFloat("Near", &perspectiveNear))
                    camera.SetPerspectiveNearClip(perspectiveNear);

                float perspectiveFar = camera.GetPerspectiveFarClip();
                if (ImGui::DragFloat("Far", &perspectiveFar))
                    camera.SetPerspectiveFarClip(perspectiveFar);
            }

            if (camera.GetProjectionType() == Camera::ProjectionType::Orthographic)
            {
                float orthoSize = camera.GetOrthographicSize();
                if (ImGui::DragFloat("Size", &orthoSize))
                    camera.SetOrthographicSize(orthoSize);

                float orthoNear = camera.GetOrthographicNearClip();
                if (ImGui::DragFloat("Near", &orthoNear))
                    camera.SetOrthographicNearClip(orthoNear);

                float orthoFar = camera.GetOrthographicFarClip();
                if (ImGui::DragFloat("Far", &orthoFar))
                    camera.SetOrthographicFarClip(orthoFar);

            }
        });

        DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [](auto& component)
        {
            ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));

            std::string& textureName = component.TextureName;
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, textureName.c_str());
            ImGui::Text("Texture: ");
            ImGui::SameLine();
            ImGui::PushItemWidth(100.0f);
            if (ImGui::InputText("##Location", buffer, sizeof(buffer)))
            {
                textureName = std::string(buffer);
            }
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushItemWidth(-1);
            if (ImGui::Button("Load"))
            {
                if (textureName != "")
                {
                    std::string fullPath = "assets/textures/" + textureName;
                    component.Texture = Texture2D::Create(fullPath);
                }
                // Load the texture
            }
            ImGui::PopItemWidth();
        });

        DrawComponent<MeshRendererComponent>("Mesh Renderer", entity, [](auto& component)
        {
            if (ImGui::Button("Create new mesh"))
                ImGui::OpenPopup("CreateMesh");
            
            if (ImGui::BeginPopup("CreateMesh"))
            {
                if (ImGui::MenuItem("Cube"))
                {
                    component.Mesh = MeshFactory::CreateCube(glm::vec3(1.0f));
                    ImGui::CloseCurrentPopup();
                }
            
                if (ImGui::MenuItem("Sphere"))
                {
                    component.Mesh = MeshFactory::CreateSphere(1.0f);
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("CustomBowl"))
                {
                    ImGui::CloseCurrentPopup();
                }
            
                if (ImGui::MenuItem("Cylinder"))
                {
                    ImGui::CloseCurrentPopup();
                }
            
                ImGui::EndPopup();
            }

            ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
            // ImGui::Text(model->GetName().c_str());
        });


        

    }

    void SceneInspectorPanel::SetSelectedEntity(Entity& entity)
    {
        m_SelectedEntity = &entity;
    }

    void SceneInspectorPanel::SetSelectedEntity(Entity* entity)
    {
        m_SelectedEntity = entity;
    }
}
