//#include "C:/Users/berka/Desktop/WheelEngine/Game/CMakeFiles/Game.dir/Debug/cmake_pch.hxx"
#include "EditorLayer.h"
#include "Renderer/Renderer2D.h"
#include <imgui.h>
#include <imguizmo.h>
#include <glm/gtc/type_ptr.inl>
#include "EditorCamera.h"
#include <Scene/SceneSerializer.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace Wheel {

    bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
    {
        // From glm::decompose in matrix_decompose.inl

        using namespace glm;
        using T = float;

        mat4 LocalMatrix(transform);

        // Normalize the matrix.
        if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
            return false;

        // First, isolate perspective.  This is the messiest.
        if (
                epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
                epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
                epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
        {
            // Clear the perspective partition
            LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
            LocalMatrix[3][3] = static_cast<T>(1);
        }

        // Next take care of translation (easy).
        translation = vec3(LocalMatrix[3]);
        LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

        vec3 Row[3], Pdum3;

        // Now get scale and shear.
        for (length_t i = 0; i < 3; ++i)
            for (length_t j = 0; j < 3; ++j)
                Row[i][j] = LocalMatrix[i][j];

        // Compute X scale factor and normalize first row.
        scale.x = length(Row[0]);
        Row[0] = detail::scale(Row[0], static_cast<T>(1));
        scale.y = length(Row[1]);
        Row[1] = detail::scale(Row[1], static_cast<T>(1));
        scale.z = length(Row[2]);
        Row[2] = detail::scale(Row[2], static_cast<T>(1));

        // At this point, the matrix (in rows[]) is orthonormal.
        // Check for a coordinate system flip.  If the determinant
        // is -1, then negate the matrix and the scaling factors.
#if 0
        Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
		if (dot(Row[0], Pdum3) < 0)
		{
			for (length_t i = 0; i < 3; i++)
			{
				scale[i] *= static_cast<T>(-1);
				Row[i] *= static_cast<T>(-1);
			}
		}
#endif

        rotation.y = asin(-Row[0][2]);
        if (cos(rotation.y) != 0) {
            rotation.x = atan2(Row[1][2], Row[2][2]);
            rotation.z = atan2(Row[0][1], Row[0][0]);
        }
        else {
            rotation.x = atan2(-Row[2][0], Row[1][1]);
            rotation.z = 0;
        }


        return true;
    }

    void SimpleDialog::OnImGuiRender()
    {
        ImGui::Begin("DialogWindow");
        ImGui::Text("Name:");
        ImGui::SameLine();
        char buffer[256];
        memset(buffer, 0, sizeof(buffer));
        strcpy(buffer, FileName.c_str());
        if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
        {
            FileName = std::string(buffer);
        }

        if (ImGui::Button(FunctionName.c_str()))
        {
            Function(FileName);
        }

        ImGui::End();
    }

    class CameraController : public ScriptableEntity
    {
    public:
        virtual void OnCreate() override
        {
            WHEEL_INFO("CameraController::OnCreate called");
        }

        virtual void OnUpdate(float deltaTime)
        {
            auto& transform = GetComponent<TransformComponent>();

            if (Input::IsKeyPressed(Key::D))
                transform.Position += glm::vec3(0.1f, 0.0f, 0.0f);
            else if (Input::IsKeyPressed(Key::A))
                transform.Position += glm::vec3(-0.1f, 0.0f, 0.0f);

            if (Input::IsKeyPressed(Key::W))
                transform.Position += glm::vec3(0.0f, 0.1f, 0.0f);
            else if (Input::IsKeyPressed(Key::S))
                transform.Position += glm::vec3(0.0f, -0.1f, 0.0f);
        }
    };

    void EditorLayer::OnAttach()
    {
        Wheel::FramebufferSpecification spec;
        spec.Width = 1280;
        spec.Height = 720;

        m_IconPlay = Texture2D::Create("resources/icons/PlayButton.png");
        m_IconStop = Texture2D::Create("resources/icons/StopButton.png");

        m_Scene = CreateRef<Scene>();

        m_CameraEntity = m_Scene->CreateEntity("CameraEntity");
        m_CameraEntity->AddComponent<CameraComponent>();
        // TODO: Refactor this to: m_Camera->AddComponent<CameraController>();
        m_CameraEntity->AddComponent<NativeScriptComponent>().Bind<CameraController>();

        m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_Scene);
        m_SceneInspectorPanel = CreateRef<SceneInspectorPanel>();
        m_ResourceBrowser = CreateRef<ResourceBrowser>();

        //m_NewSceneDialog = CreateRef<SimpleDialog>("Create", std::bind(&EditorLayer::NewScene, this, std::placeholders::_1));
        m_LoadSceneDialog = CreateRef<SimpleDialog>("Load", std::bind(&EditorLayer::LoadScene, this, std::placeholders::_1));
        m_SaveSceneDialog = CreateRef<SimpleDialog>("Save", std::bind(&EditorLayer::SaveScene, this, std::placeholders::_1));
//        m_SaveSceneDialog = CreateRef<SimpleDialog>();

        m_Framebuffer = Wheel::Framebuffer::Create(spec);

        m_EditorCamera = CreateRef<EditorCamera>(45, 1.7, 0.1f, 10000.0f);

        SceneSerializer serializer(m_Scene);
    }

    void EditorLayer::OnDetach()
    {

    }

    void EditorLayer::OnUpdate(float deltaTime)
    {
        if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
                m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
                (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
        {
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_EditorCamera->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
            m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }

        m_Framebuffer->Bind();
        Wheel::RenderCommand::SetClearColor({ 0.01f, 0.01f, 0.07f, 1.0f });
        Wheel::RenderCommand::Clear();

        // m_Scene->OnUpdate(deltaTime);

        // m_EditorCamera->OnUpdate(deltaTime);

        switch (m_SceneState)
        {
            case SceneState::Edit:
            {
                if (m_ViewportFocused)
                    //m_CameraEntity->OnUpdate(deltaTime);

                m_EditorCamera->OnUpdate(deltaTime);

                m_Scene->OnUpdateEditor(deltaTime, *m_EditorCamera.get());
                break;
            }
            case SceneState::Play:
            {
                m_Scene->OnUpdate(deltaTime);
                break;
            }
        }

        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {
        // Note: Switch this to true to enable dockspace
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
                if (ImGui::MenuItem("New", "Ctrl+N"))
                {
                    NewScene();
                    //m_NewSceneDialog->Active = true;
                }


                if (ImGui::MenuItem("Load...", "Ctrl+O"))
                {
                    m_LoadSceneDialog->Active = true;
                }

                if (ImGui::MenuItem("Save...", "Ctrl+S"))
                {
                    m_SaveSceneDialog->Active = true;
                }

//                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
//                    //SaveSceneAs();

                if (ImGui::MenuItem("Exit")) Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

//        if (m_NewSceneDialog->Active)
//        {
//            m_NewSceneDialog->OnImGuiRender();
//        }

        if (m_LoadSceneDialog->Active)
        {
            m_LoadSceneDialog->OnImGuiRender();
        }

        if (m_SaveSceneDialog->Active)
        {
            m_SaveSceneDialog->OnImGuiRender();
        }

        m_SceneHierarchyPanel->OnImGuiRender();

        m_SceneInspectorPanel->SetSelectedEntity(m_SceneHierarchyPanel->GetSelectedEntity());
        m_SceneInspectorPanel->OnImGuiRender();

        m_ResourceBrowser->OnImGuiRender();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        // TODO: This will change there will be 2 viewports one for editor and for the game
        ImGui::Begin("Viewport");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImVec2 availRegion = ImGui::GetContentRegionAvail();
        m_ViewportSize = { availRegion.x, availRegion.y };

        // Flip the image
        ImGui::Image((void*)textureID, {m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});

        Entity* selectedEntity = &m_SceneHierarchyPanel->GetSelectedEntity();
        if (selectedEntity && !selectedEntity->HasComponent<CameraComponent>() && m_GizmoType != -1)
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            float windowWidth = (float)ImGui::GetWindowWidth();
            float windowHeight = (float)ImGui::GetWindowHeight();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

            // Camera
            const glm::mat4& cameraProjection = m_EditorCamera->GetProjectionMatrix();
            glm::mat4 cameraView = m_EditorCamera->GetViewMatrix();

            // Entity transform
            auto& tc = selectedEntity->GetComponent<TransformComponent>();
            glm::mat4 transform = tc.GetTransform();

            float snapValues[3] = { 0.1f, 1.0f, 0.1f };

            if (m_SceneState == SceneState::Edit)
                ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
                                 (ImGuizmo::OPERATION) m_GizmoType, ImGuizmo::WORLD, glm::value_ptr(transform),
                                 nullptr, snapValues);

            if (ImGuizmo::IsUsing())
            {
                glm::vec3 position, rotation, scale;
                DecomposeTransform(transform, position, rotation, scale);

                glm::vec3 deltaRotation = rotation - tc.Rotation;
                tc.Position = position;
                if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
                    tc.Rotation += deltaRotation;
                tc.Scale = scale;
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();

        UI_Toolbar();

        ImGui::End();
    }

    void EditorLayer::OnEvent(Wheel::Event& e)
    {
        Wheel::EventDispatcher dispatcher(e);

        dispatcher.Dispatch<Wheel::WindowResizeEvent>(std::bind(&EditorLayer::OnScreenResize, this, std::placeholders::_1));
        dispatcher.Dispatch<Wheel::KeyPressedEvent>(std::bind(&EditorLayer::OnKeyPressed, this, std::placeholders::_1));

    }

    bool EditorLayer::OnKeyPressed(Wheel::KeyPressedEvent& e)
    {
        if (e.GetRepeatCount() > 0)
            return false;

        bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
        bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);

        if (m_SceneState != SceneState::Edit || !m_ViewportFocused)
            return true;

        switch (e.GetKeyCode())
        {
            case Key::N:
            {
                if (control)
                    m_NewSceneDialog->Active = true;

                break;
            }
            case Key::O:
            {
                if (control)
                    m_LoadSceneDialog->Active = true;

                break;
            }
            case Key::S:
            {
                if (control && shift)
                    m_SaveSceneDialog->Active = true;

                break;
            }

                // Gizmos
            case Key::Q:
            {
                if (!ImGuizmo::IsUsing())
                    m_GizmoType = -1;
                break;
            }
            case Key::W:
            {
                if (!ImGuizmo::IsUsing())
                    m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
                break;
            }
            case Key::E:
            {
                if (!ImGuizmo::IsUsing())
                    m_GizmoType = ImGuizmo::OPERATION::ROTATE;
                break;
            }
            case Key::R:
            {
                if (!ImGuizmo::IsUsing())
                    m_GizmoType = ImGuizmo::OPERATION::SCALE;
                break;
            }
        }

    }

    bool EditorLayer::OnScreenResize(Wheel::WindowResizeEvent& e)
    {
        return false;
    }

    void EditorLayer::NewScene()
    {
        m_SceneInspectorPanel->SetSelectedEntity(nullptr);
        m_Scene = CreateRef<Scene>();
        m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        m_SceneHierarchyPanel->SetContext(m_Scene);

        m_NewSceneDialog->Active = false;
    }

    void EditorLayer::NewScene(std::string name)
    {
        m_SceneInspectorPanel->SetSelectedEntity(nullptr);
        m_Scene = CreateRef<Scene>();
        m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        m_SceneHierarchyPanel->SetContext(m_Scene);

        m_NewSceneDialog->Active = false;
    }

    void EditorLayer::LoadScene(std::string name)
    {
        m_SceneInspectorPanel->SetSelectedEntity(nullptr);
        m_Scene = CreateRef<Scene>();
        SceneSerializer serializer(m_Scene);

        m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        m_SceneHierarchyPanel->SetContext(m_Scene);

        std::string fullPath = "assets/scenes/" + name;
        serializer.Deserialize(fullPath);

        m_LoadSceneDialog->Active = false;
        //std::string filepath = FileDialogs::OpenFile("Hazel Scene (*.hazel)\0*.hazel\0");
//        if (!filepath.empty())
//            OpenScene(filepath);
    }

    void EditorLayer::OpenScene(const std::filesystem::path& path)
    {
        if (path.extension().string() != ".hazel")
        {
            WHEEL_CORE_WARN("Could not load {0} - not a scene file", path.filename().string());
            return;
        }

        Ref<Scene> newScene = CreateRef<Scene>();
        SceneSerializer serializer(newScene);
        if (serializer.Deserialize(path.string()))
        {
            m_Scene = newScene;
            m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_SceneHierarchyPanel->SetContext(m_Scene);
        }
    }

    void EditorLayer::SaveScene(std::string name)
    {
        SceneSerializer serializer(m_Scene);
        std::string path = "assets/scenes/" + name;
        serializer.Serialize(path);

        m_SaveSceneDialog->Active = false;
    }

    void EditorLayer::UI_Toolbar()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        auto& colors = ImGui::GetStyle().Colors;
        const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
        const auto& buttonActive = colors[ImGuiCol_ButtonActive];
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

        ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        float size = ImGui::GetWindowHeight() - 4.0f;
        Ref<Texture2D> icon = m_SceneState == SceneState::Edit ? m_IconPlay : m_IconStop;
        ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
        if (ImGui::ImageButton((ImTextureID)icon->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0))
        {
            if (m_SceneState == SceneState::Edit)
                OnScenePlay();
            else if (m_SceneState == SceneState::Play)
                OnSceneStop();
        }
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);
        ImGui::End();
    }

    void EditorLayer::OnScenePlay()
    {
        m_SceneState = SceneState::Play;
    }

    void EditorLayer::OnSceneStop()
    {
        m_SceneState = SceneState::Edit;

    }



}


