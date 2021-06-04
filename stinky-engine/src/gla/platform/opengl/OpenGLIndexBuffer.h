#pragma once

#include "gla/IndexBuffer.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OpenGLIndexBuffer : public IndexBuffer {
    private:
        uint32_t m_RendererID;
        const uint32_t m_Count;
    public:
        OpenGLIndexBuffer(const void *data, uint32_t count);

        ~OpenGLIndexBuffer() override;

        void Bind() const override;

        void Unbind() const override;

        [[nodiscard]] uint32_t GetCount() const override {
            return m_Count;
        }
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////