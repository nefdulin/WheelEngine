#include <iostream>
#include <Wheel.h>
#include <imgui.h>

class ExampleLayer : public Wheel::Layer
{

    virtual void OnAttach() override
    {
        std::string vertexSrc = R"(
			#version 330 core

            uniform mat4 u_MVP;
			layout(location = 0) in vec3 a_Position;
			void main()
			{
				gl_Position = u_MVP * vec4(a_Position, 1.0);
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core

			out vec4 color;
			void main()
			{
				color = vec4(1.0, 1.0, 1.0, 1.0);
			}
		)";

        m_Shader = new Wheel::OpenGLShader(vertexSrc, fragmentSrc);
        m_Shader->Bind();

        m_Camera = new Wheel::OrthographicCamera(-2.0f, 2.0f, -2.0f, 2.0f);
        m_Camera->SetPosition(glm::vec3(1));

        float vertices[] = {
0.5f,  0.5f, 0.0f,  // top right
0.5f, -0.5f, 0.0f,  // bottom right
-0.5f, -0.5f, 0.0f,  // bottom left
-0.5f,  0.5f, 0.0f   // top left 
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

        m_VertexArray = new Wheel::OpenGLVertexArray();

        Wheel::VertexBuffer* vb = new Wheel::OpenGLVertexBuffer(vertices, sizeof(vertices));
        Wheel::BufferLayout layout = {
            {Wheel::ShaderDataType::Float3, "a_Position"}
        };
        vb->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vb);
        std::shared_ptr<Wheel::IndexBuffer> ib = std::make_shared<Wheel::OpenGLIndexBuffer>(indices, 6);
        m_VertexArray->SetIndexBuffer(ib);
    }

    virtual void OnUpdate(float deltaTime) override
    {
        WHEEL_TRACE("Current delta time is: {0}s {1}ms", deltaTime, deltaTime * 1000);

        Wheel::RenderCommand::SetClearColor({0.09f, 0.09f, 0.12f, 1.0f});
        Wheel::RenderCommand::Clear();

        m_Shader->Bind();
        m_Shader->SetMat4("u_MVP", m_Camera->GetViewProjectionMatrix());
        Wheel::Renderer::BeginScene();
        Wheel::RenderCommand::DrawIndexed(m_VertexArray);
        Wheel::Renderer::EndScene();

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
    Wheel::Camera * m_Camera;
    Wheel::Shader* m_Shader;
    Wheel::VertexArray* m_VertexArray;
};

class GameApp : public Wheel::Application
{
public:
    GameApp()
    {
        Wheel::Layer* layer = new ExampleLayer();
        PushLayer(layer);
    }

    ~GameApp()
    {

    }
};

Wheel::Application* Wheel::CreateApplication()
{
    return new GameApp();
}