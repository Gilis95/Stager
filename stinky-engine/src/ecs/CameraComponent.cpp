//
// Created by christian on 14/10/2020.
//

#include "CameraComponent.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    CameraComponent::CameraComponent(Camera *camera, bool isPrimary)
        : m_Camera(camera)
        , m_IsPrimary(isPrimary) {
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
