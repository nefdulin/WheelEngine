#pragma once
#include "Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Wheel {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        const std::vector<VertexBuffer*>    GetVertexBuffers() const override { return m_VertexBuffers; }
        const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID;
        std::vector<VertexBuffer*> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}
