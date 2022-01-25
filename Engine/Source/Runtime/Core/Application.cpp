#include "Application.h"
#include "Log.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer/OrthographicCamera.h"

namespace Wheel {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        WHEEL_CORE_ASSERT(s_Instance == nullptr, "An application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer.get());

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

        m_Shader = new Shader(vertexSrc, fragmentSrc);
        m_Shader->Bind();


        m_Camera = new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {

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

        VertexArray* va = new OpenGLVertexArray();

        VertexBuffer* vb = new OpenGLVertexBuffer(vertices, sizeof(vertices));
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"}
        };
        vb->SetLayout(layout);
        va->AddVertexBuffer(vb);
        std::shared_ptr<IndexBuffer> ib = std::make_shared<OpenGLIndexBuffer>(indices, 6);
        va->SetIndexBuffer(ib);
        
        m_Camera->SetPosition(glm::vec3(1));
        while (m_Running)
        {
            RenderCommand::SetClearColor();
            RenderCommand::Clear();

            m_Shader->SetMat4("u_MVP", m_Camera->GetViewProjectionMatrix());
            Renderer::BeginScene();
            RenderCommand::DrawIndexed(va);
            Renderer::EndScene();

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Camera->OnUpdate();
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Application::OnMouseMoved, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    bool Application::OnMouseMoved(MouseMovedEvent& e)
    {
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        WHEEL_CORE_TRACE("Window resizing");
        return true;
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        WHEEL_CORE_ERROR("Window close event triggered, application stopped!");
        m_Running = 0;
        return true;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
}