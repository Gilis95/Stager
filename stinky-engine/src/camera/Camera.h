//
// Created by christian on 12/10/2020.
//

#pragma once

#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Camera {
    public:
        explicit Camera(glm::mat4 &projectionMatrix);
        explicit Camera(glm::mat4 &&projectionMatrix);

        Camera(Camera &&camera) noexcept;

        virtual ~Camera() = default;

        [[nodiscard]] const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }

        [[nodiscard]] const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }

        [[nodiscard]] const glm::mat4 &GetViewProjectionMatrix() {
            RecalculateViewMatrix();
            return m_ViewProjectionMatrix;
        }

        void SetPosition(const glm::vec3 &pos) {
            m_Position = pos;
            m_ViewDirty = true;
        }

        [[nodiscard]]const glm::vec3 &GetPosition() const {
            return m_Position;
        }

    protected:
        virtual void RecalculateViewMatrix() = 0;

    protected:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix{1.0f};
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position{};

        bool m_ViewDirty = false;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////