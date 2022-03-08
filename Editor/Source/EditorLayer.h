#pragma once
#include <Wheel.h>

namespace Wheel {
    class EditorLayer : public Wheel::Layer
    {
        virtual void OnAttach() override;
        virtual void OnDetach() override;

        virtual void OnUpdate(float deltaTime) override;
        virtual void OnEvent(Wheel::Event& e) override;

        virtual void OnImGuiRender() override;

        bool OnScreenResize(Wheel::WindowResizeEvent& e);
    private:
        Ref<Wheel::Camera> m_Camera;
        Ref<Wheel::Texture> m_GalaxyTexture;
        Ref<Wheel::Framebuffer> m_Framebuffer;
        Ref<Scene> m_Scene;
        Ref<Entity> m_Entity;

        bool m_ViewportHovered = true;
        bool m_ViewportFocused = true;
        glm::vec2 m_ViewportSize;
    };
}



