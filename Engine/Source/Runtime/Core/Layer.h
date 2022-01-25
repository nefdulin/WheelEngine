#pragma once
#include "Events/Event.h"

namespace Wheel {

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnEvent(Event& event) {}

        virtual void OnImGuiRender() {}

        inline const std::string& GetName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
    };

}



