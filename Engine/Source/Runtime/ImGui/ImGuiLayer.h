#pragma once
#include "Core/Layer.h"
#include "Events/ApplicationEvent.h"

namespace Wheel {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        virtual void OnImGuiRender() override;
        virtual void OnEvent(Event& event) override;

        void SetDarkThemeColors();
        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };

}


