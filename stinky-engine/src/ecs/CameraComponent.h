//
// Created by christian on 12/10/2020.
//

#pragma once

#include "camera/Camera.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class CameraComponent {
    public:
        explicit CameraComponent(Camera *camera, bool isPrimary = false);
    public:
        Camera *m_Camera;
        bool m_IsPrimary;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////