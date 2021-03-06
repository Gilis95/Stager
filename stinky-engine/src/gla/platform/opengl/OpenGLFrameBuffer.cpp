//
// Created by christian on 10/08/2020.
//

#include "stinkypch.h"
#include "gla/platform/opengl/OpenGLFrameBuffer.h"
#include <glad/glad.h>

namespace stinky {
    static const uint32_t s_MaxFrameBufferSize = 8192;

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification &spec)
            : FrameBuffer(spec), m_RendererID(0), m_ColorAttachment(0), m_DepthAttachment(0) {
        Invalidate();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLFrameBuffer::~OpenGLFrameBuffer() {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(1, &m_ColorAttachment);
        glDeleteTextures(1, &m_DepthAttachment);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLFrameBuffer::Invalidate() {
        if (m_RendererID) {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        glGenTextures(1, &m_ColorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Specification.Width, m_Specification.Height, 0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                               m_ColorAttachment, 0);

        glGenTextures(1, &m_DepthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width,
                       m_Specification.Height);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
                               m_DepthAttachment, 0);

        AssertLogUnless(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
                        "Frame buffer is incomplete!")

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLFrameBuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Specification.Width, m_Specification.Height);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLFrameBuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLFrameBuffer::WindowResize(uint32_t width, uint32_t height) {
        ReturnIf(width == 0 || height == 0 || width > s_MaxFrameBufferSize ||
                 height > s_MaxFrameBufferSize)

        m_Specification.Width = width;
        m_Specification.Height = height;

        Invalidate();
    }
}