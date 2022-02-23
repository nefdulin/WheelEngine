//#include "C:/Users/berka/Desktop/WheelEngine/Game/CMakeFiles/Game.dir/Debug/cmake_pch.hxx"
#include "EditorLayer.h"
#include "Renderer/Renderer2D.h"
#include <imgui.h>

void EditorLayer::OnAttach()
{
    m_Camera = Wheel::CreateRef<Wheel::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);
    m_GalaxyTexture = Wheel::Texture2D::Create("assets/textures/test.png");
	Wheel::FramebufferSpecification spec; 
	spec.Width = 1280;
	spec.Height = 720;
	m_Framebuffer = Wheel::Framebuffer::Create(spec);

}

void EditorLayer::OnDetach()
{

}

void EditorLayer::OnUpdate(float deltaTime)
{
	m_Framebuffer->Bind();
    Wheel::RenderCommand::SetClearColor({ 0.01f, 0.01f, 0.07f, 1.0f });
    Wheel::RenderCommand::Clear();

    Wheel::Renderer2D::BeginScene(m_Camera);
    // Wheel::Renderer2D::DrawQuad(glm::vec3(1.0f), glm::vec3(1.0f), m_GalaxyTexture);
    Wheel::Renderer2D::DrawQuad(glm::vec3(0.0f), glm::vec3(0.1f), {1.0f, 0.2f, 0.3f, 1.0f});
    Wheel::Renderer2D::EndScene();

	glm::vec3 newPosition = m_Camera->GetPosition();
	if (Wheel::Input::IsKeyPressed(Wheel::Key::D))
		newPosition.x += 1.0f * deltaTime;
	else if (Wheel::Input::IsKeyPressed(Wheel::Key::A))
		newPosition.x -= 1.0f * deltaTime;

	if (Wheel::Input::IsKeyPressed(Wheel::Key::W))
		newPosition.y += 1.0f * deltaTime;
	else if (Wheel::Input::IsKeyPressed(Wheel::Key::S))
		newPosition.y -= 1.0f * deltaTime;

	m_Camera->SetPosition(newPosition);

    m_Camera->OnUpdate();

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

	ImGui::Begin("Settings");
	ImGui::Text("Test");
	ImGui::End();

	ImGui::Begin("Scene");
	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	ImVec2 availRegion = ImGui::GetContentRegionAvail();
	if (m_ViewportSize != *((glm::vec2*)&availRegion))
	{
		m_Framebuffer->Resize((uint32_t)availRegion.x, (uint32_t)availRegion.y);
		m_ViewportSize = { availRegion.x, availRegion.y };
	}
	// Flip the image
	ImGui::Image((void*)textureID, {m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});;
	ImGui::End();
	ImGui::End();
}

void EditorLayer::OnEvent(Wheel::Event& e)
{
    Wheel::EventDispatcher dispatcher(e);

    dispatcher.Dispatch<Wheel::WindowResizeEvent>(std::bind(&EditorLayer::OnScreenResize, this, std::placeholders::_1));
}

bool EditorLayer::OnScreenResize(Wheel::WindowResizeEvent& e)
{
	m_Framebuffer->Resize(e.GetWidth(), e.GetHeight());

    return false;
}