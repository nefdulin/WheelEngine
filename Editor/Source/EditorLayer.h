#pragma once
#include <Wheel.h>
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/SceneInspectorPanel.h"
#include "Panels/ResourceBrowser.h"
#include "EditorCamera.h"

namespace Wheel {

    class SimpleDialog
    {
    public:
        SimpleDialog(std::string name, std::function<void(std::string)> function)
        {
            FunctionName = name;
            Function = function;
        }

        void OnImGuiRender();

        void SetText(const std::string& text);
    public:
        bool Active = false;
        std::string FunctionName = "";
        std::string FileName = "";
        std::function<void(std::string)> Function;
    };


    class EditorLayer : public Wheel::Layer
    {
        virtual void OnAttach() override;
        virtual void OnDetach() override;

        virtual void OnUpdate(float deltaTime) override;
        virtual void OnEvent(Wheel::Event& e) override;

        virtual void OnImGuiRender() override;

        bool OnScreenResize(Wheel::WindowResizeEvent& e);
    public:
        void NewScene();
        void NewScene(std::string name);
        void LoadScene(std::string name);
        void OpenScene(const std::filesystem::path& path);
        void SaveScene(std::string name);

    private:
        Ref<EditorCamera> m_EditorCamera;
        Ref<Wheel::Framebuffer> m_Framebuffer;
        Ref<Scene> m_Scene;
        Ref<Entity> m_Entity;
        Ref<Entity> m_CameraEntity;
        Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;
        Ref<SceneInspectorPanel> m_SceneInspectorPanel;
        Ref<ResourceBrowser> m_ResourceBrowser;
        Ref<SimpleDialog> m_NewSceneDialog;
        Ref<SimpleDialog> m_LoadSceneDialog;
        Ref<SimpleDialog> m_SaveSceneDialog;

        bool m_ViewportHovered = true;
        bool m_ViewportFocused = true;
        glm::vec2 m_ViewportSize;
    };
}



