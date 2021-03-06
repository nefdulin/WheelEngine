//#include "C:/Users/berka/Desktop/WheelEngine/Game/CMakeFiles/Game.dir/Debug/cmake_pch.hxx"
#include "Sandbox2DLayer.h"
#include "Renderer/Renderer2D.h"
#include <imgui.h>

void Sandbox2DLayer::OnAttach()
{
    m_Camera = Wheel::CreateRef<Wheel::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);
    m_GalaxyTexture = Wheel::Texture2D::Create("assets/textures/test.png");
	Wheel::FramebufferSpecification spec; 
	spec.Width = 1280;
	spec.Height = 720;
	m_Framebuffer = Wheel::Framebuffer::Create(spec);
}

void Sandbox2DLayer::OnDetach()
{

}

void Sandbox2DLayer::OnUpdate(float deltaTime)
{
	m_Framebuffer->Bind();
    Wheel::RenderCommand::SetClearColor({ 0.01f, 0.01f, 0.07f, 1.0f });
    Wheel::RenderCommand::Clear();

    Wheel::Renderer2D::BeginScene(m_Camera);
    // Wheel::Renderer2D::DrawQuad(glm::vec3(1.0f), glm::vec3(1.0f), m_GalaxyTexture);
    Wheel::Renderer2D::DrawQuad(glm::vec3(0.0f), glm::vec3(0.1f), {1.0f, 0.2f, 0.3f, 1.0f});
    Wheel::Renderer2D::EndScene();

    m_Camera->OnUpdate();

	m_Framebuffer->Unbind();
}

void Sandbox2DLayer::OnImGuiRender()
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

	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	
	// Flip the image
	ImGui::Image((void*)textureID, ImVec2(1280, 720), ImVec2{0, 1}, ImVec2{1, 0});;
	ImGui::End();
	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Wheel::Event& e)
{
    Wheel::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<Wheel::WindowResizeEvent>(std::bind(&Sandbox2DLayer::OnScreenResize, this, std::placeholders::_1));
}

bool Sandbox2DLayer::OnScreenResize(Wheel::WindowResizeEvent& e)
{
    return false;
}
