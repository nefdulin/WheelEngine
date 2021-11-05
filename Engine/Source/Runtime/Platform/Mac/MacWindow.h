#pragma once
#include "Core/Window.h"

struct GLFWwindow;

namespace Wheel {

    class MacWindow : public Window
    {
    public:
        MacWindow(const WindowProps& props);
        virtual ~MacWindow();

        void OnUpdate() override;

        inline uint32_t GetWidth() const override { return m_Data.width; }
        inline uint32_t GetHeight() const override { return m_Data.height; }

        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string title;
            uint32_t width;
            uint32_t height;
            bool VSync;

            EventCallbackFn  EventCallback;
        };

        WindowData m_Data;
    };

}


