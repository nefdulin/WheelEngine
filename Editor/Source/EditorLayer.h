#pragma once
#include <Wheel.h>

class EditorLayer : public Wheel::Layer
{
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnEvent(Wheel::Event& e) override;

	virtual void OnImGuiRender() override;
	
	bool OnScreenResize(Wheel::WindowResizeEvent& e);
private:
	Wheel::Ref<Wheel::Camera> m_Camera;
	Wheel::Ref<Wheel::Texture> m_GalaxyTexture;
	Wheel::Ref<Wheel::Framebuffer> m_Framebuffer;

	glm::vec2 m_ViewportSize;
};

