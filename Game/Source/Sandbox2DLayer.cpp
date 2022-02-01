//#include "C:/Users/berka/Desktop/WheelEngine/Game/CMakeFiles/Game.dir/Debug/cmake_pch.hxx"
#include "Sandbox2DLayer.h"
#include "Renderer/Renderer2D.h"

void Sandbox2DLayer::OnAttach()
{
    m_Camera = Wheel::CreateRef<Wheel::OrthographicCamera>(-2.0f, 2.0f, -2.0f, 2.0f);
    m_GalaxyTexture = Wheel::Texture2D::Create("assets/textures/test.png");
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(float deltaTime)
{
    Wheel::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.1f, 0.8f });
    Wheel::RenderCommand::Clear();

    Wheel::Renderer2D::BeginScene(m_Camera);
    Wheel::Renderer2D::DrawQuad(glm::vec3(1.0f), glm::vec3(1.0f), m_GalaxyTexture);
    Wheel::Renderer2D::EndScene();

    m_Camera->OnUpdate();
}

void Sandbox2DLayer::OnEvent(Wheel::Event& e)
{
}

void Sandbox2DLayer::OnImGuiRender()
{
}
