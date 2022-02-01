#pragma once
#include <Wheel.h>

class Sandbox2DLayer : public Wheel::Layer
{
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnEvent(Wheel::Event& e) override;

	virtual void OnImGuiRender() override;
private:
	Wheel::Ref<Wheel::Camera> m_Camera;
	Wheel::Ref<Wheel::Texture> m_GalaxyTexture;
};

