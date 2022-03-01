#include <iostream>
#include <Wheel.h>
#include <imgui.h>
#include <Core/EntryPoint.h>
#include "EditorLayer.h"

class ExampleLayer : public Wheel::Layer
{

    virtual void OnAttach() override
    {
        std::string vertexSrc = R"(
			#version 330 core

            uniform mat4 u_MVP;
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

            out vec2 texCoord;
			void main()
			{
                texCoord = a_TexCoord;
				gl_Position = u_MVP * vec4(a_Position, 1.0);
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core
            
            uniform sampler2D u_Texture;
    
            in vec2 texCoord;
			out vec4 color;
			void main()
			{
				color = vec4(texCoord, 0.0, 1.0) * texture(u_Texture, texCoord);
			}
		)";

        m_ShaderLibrary = std::make_shared<Wheel::ShaderLibrary>();
        m_Shader = m_ShaderLibrary->Load("assets/shaders/Texture.glsl");

        m_Shader->Bind();

        m_Camera = Wheel::CreateRef<Wheel::OrthographicCamera>(-2.0f, 2.0f, -2.0f, 2.0f);
        glm::vec3 position(1.0f);
        m_Camera->SetPosition(position);

        float vertices[] = {
             0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // top right
             0.5f,   0.5f, 0.0f, 1.0f, 1.0f, // bottom right
            -0.5f,   0.5f, 0.0f, 0.0f, 1.0f,      // bottom left
            -0.5f,  -0.5f, 0.0f, 0.0f, 0.0f  // top left 
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 2,  // first Triangle
            0, 2, 3   // second Triangle
        };

        m_VertexArray = Wheel::VertexArray::CreateVertexArray();

        Wheel::Ref<Wheel::VertexBuffer> vb = Wheel::VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices));
        Wheel::BufferLayout layout = {
            {Wheel::ShaderDataType::Float3, "a_Position"},
            {Wheel::ShaderDataType::Float2, "a_TexCoords"}
        };
        vb->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vb);

        std::shared_ptr<Wheel::IndexBuffer> ib = std::make_shared<Wheel::OpenGLIndexBuffer>(indices, 6);
        m_VertexArray->SetIndexBuffer(ib);

        m_Texture = Wheel::Texture2D::Create("assets/textures/test.png");
        m_Texture->Bind();

        m_Shader->SetInt("u_Texture", 0);
    }

    virtual void OnUpdate(float deltaTime) override
    {
        Wheel::RenderCommand::SetClearColor({0.01f, 0.01f, 0.07f, 1.0f});
        Wheel::RenderCommand::Clear();

        m_Shader->Bind();
        m_Shader->SetMat4("u_MVP", m_Camera->GetViewProjectionMatrix());
        //m_Texture->Bind();
        Wheel::Renderer::BeginScene();
        Wheel::RenderCommand::DrawIndexed(m_VertexArray);
        Wheel::Renderer::EndScene();

        Wheel::Renderer2D::BeginScene(m_Camera);
        Wheel::Renderer2D::DrawQuad(glm::vec3(1.0f), glm::vec3(0.3f), m_Texture);
        Wheel::Renderer2D::DrawQuad(glm::vec3(0.5f), glm::vec3(0.6f), m_Texture);
        Wheel::Renderer2D::EndScene();

        m_Camera->OnUpdate();
        if (Wheel::Input::IsKeyPressed(Wheel::Key::W))
        {
            glm::vec3 cameraPosition = m_Camera->GetPosition();
            glm::vec3 newPosition{ cameraPosition.x, cameraPosition.y - 0.01, cameraPosition.z };
            m_Camera->SetPosition(newPosition);
        }

        if (Wheel::Input::IsKeyPressed(Wheel::Key::D))
        {
            glm::vec3 cameraPosition = m_Camera->GetPosition();
            glm::vec3 newPosition{ cameraPosition.x - 0.01, cameraPosition.y, cameraPosition.z };
            m_Camera->SetPosition(newPosition);
        }
    }

    virtual void OnImGuiRender() override
    {
        bool my_tool_active = true;
        float my_color[4];
        ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
                if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

    // Edit a color (stored as ~4 floats)
        ImGui::ColorEdit4("Color", my_color);

// Plot some values
        const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
        ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

// Display contents in a scrolling region
        ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
        ImGui::BeginChild("Scrolling");
        for (int n = 0; n < 50; n++)
            ImGui::Text("%04d: Some text", n);
        ImGui::EndChild();
        ImGui::End();
    }

private:
    Wheel::Ref<Wheel::Camera> m_Camera;
    Wheel::Ref<Wheel::Shader> m_Shader;
    Wheel::Ref<Wheel::VertexArray> m_VertexArray;
    Wheel::Ref<Wheel::Texture> m_Texture;
    Wheel::Ref<Wheel::ShaderLibrary> m_ShaderLibrary;
};

class EditorApp : public Wheel::Application
{
public:
    EditorApp(const std::string& name, uint32_t width, uint32_t height)
        : Wheel::Application(name, width, height)
    {
        // Wheel::Layer* layer = new ExampleLayer();
        Wheel::Layer* l2 = new EditorLayer();
        PushLayer(l2);
    }

    ~EditorApp()
    {

    }
};

Wheel::Application* Wheel::CreateApplication()
{
    return new EditorApp("Wheel Editor", 1280, 720);
}