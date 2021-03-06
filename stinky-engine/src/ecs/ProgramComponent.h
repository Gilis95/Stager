//
// Created by christian on 19/10/2020.
//
#pragma once

#include <string>

#include "StinkyPrerequisites.h"
#include "core/StinkyMemory.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    class ProgramComponent {
    public:
        explicit ProgramComponent(Ref<Shader> program);
        ProgramComponent(ProgramComponent &&path) noexcept = default;

        ~ProgramComponent() = default;

        ProgramComponent &operator=(ProgramComponent &&copy) noexcept {
            program = copy.program;
            return *this;
        };

        Ref<Shader> program;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////