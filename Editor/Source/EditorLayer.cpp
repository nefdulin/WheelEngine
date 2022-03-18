//#include "C:/Users/berka/Desktop/WheelEngine/Game/CMakeFiles/Game.dir/Debug/cmake_pch.hxx"
#include "EditorLayer.h"
#include "Renderer/Renderer2D.h"
#include <imgui.h>
#include <imguizmo.h>
#include <glm/gtc/type_ptr.inl>

namespace Wheel {

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
        //m_Camera = Wheel::CreateRef<Wheel::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);
        m_GalaxyTexture = Wheel::Texture2D::Create("assets/textures/test.png");
        Wheel::FramebufferSpecification spec;
        spec.Width = 1280;
        spec.Height = 720;

        m_Scene = CreateRef<Scene>();

        m_CameraEntity = m_Scene->CreateEntity("CameraEntity");
        m_CameraEntity->AddComponent<CameraComponent>();
        // TODO: Refactor this to: m_Camera->AddComponent<CameraController>();
        m_CameraEntity->AddComponent<NativeScriptComponent>().Bind<CameraController>();

        m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_Scene);
        m_SceneInspectorPanel = CreateRef<SceneInspectorPanel>();
        m_Framebuffer = Wheel::Framebuffer::Create(spec);
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

            m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }

        m_Framebuffer->Bind();
        Wheel::RenderCommand::SetClearColor({ 0.01f, 0.01f, 0.07f, 1.0f });
        Wheel::RenderCommand::Clear();

        m_Scene->OnUpdate(deltaTime);

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
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                if (ImGui::MenuItem("Exit")) Wheel::Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        m_SceneHierarchyPanel->OnImGuiRender();

        m_SceneInspectorPanel->SetSelectedEntity(m_SceneHierarchyPanel->GetSelectedEntity());
        m_SceneInspectorPanel->OnImGuiRender();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImVec2 availRegion = ImGui::GetContentRegionAvail();
        m_ViewportSize = { availRegion.x, availRegion.y };

        // Flip the image
        ImGui::Image((void*)textureID, {m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});

        Entity* selectedEntity = &m_SceneHierarchyPanel->GetSelectedEntity();
        if (selectedEntity && !selectedEntity->HasComponent<CameraComponent>())
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            float windowWidth = (float)ImGui::GetWindowWidth();
            float windowHeight = (float)ImGui::GetWindowHeight();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

            // Camera
            auto cameraEntity = m_CameraEntity;
            const auto& camera = cameraEntity->GetComponent<CameraComponent>().Camera;
            const glm::mat4& cameraProjection = camera.GetProjectionMatrix();
            glm::mat4 cameraView = glm::inverse(cameraEntity->GetComponent<TransformComponent>().GetTransform());

            // Entity transform
            auto& tc = selectedEntity->GetComponent<TransformComponent>();
            glm::mat4 transform = tc.GetTransform();

            ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
                                 ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(transform),
                                 nullptr, nullptr);

            if (ImGuizmo::IsUsing())
            {
                glm::vec3 position, rotation, scale;
                ImGuizmo::DecomposeMatrixToComponents((float*) &transform[0], glm::value_ptr(position), glm::value_ptr(rotation), glm::value_ptr(scale));

                glm::vec3 deltaRotation = rotation - tc.Rotation;
                tc.Position = position;
                tc.Rotation += deltaRotation;
                tc.Scale = scale;
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
    }

    void EditorLayer::OnEvent(Wheel::Event& e)
    {
        Wheel::EventDispatcher dispatcher(e);

        dispatcher.Dispatch<Wheel::WindowResizeEvent>(std::bind(&EditorLayer::OnScreenResize, this, std::placeholders::_1));
    }

    bool EditorLayer::OnScreenResize(Wheel::WindowResizeEvent& e)
    {
        return false;
    }
}


