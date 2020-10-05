//
// Created by christian on 1/19/20.
//
#include <glad/glad.h>
#include "gla/platform/opengl/OpenGLIndexBuffer.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLIndexBuffer::OpenGLIndexBuffer(const void *data, unsigned int count) : m_Count(count),
                                                                                 m_RendererID(0) {
        glGenBuffers(1, &m_RendererID);

        // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
        // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}