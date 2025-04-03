#pragma once

#include <common.hpp>

#include <sead/math/seadVector.hpp>

#include "Sys/Scene/Scene.hpp"

namespace SampleLua {
    struct Scene : Lp::Sys::Scene {
        SEAD_RTTI_OVERRIDE(Scene, Lp::Sys::Scene);

        uintptr_t field_230;
        uintptr_t field_238;
        sead::Vector2f mCursor;
        int field_248;

        Scene(sead::Heap*);
    };
    static_assert(sizeof(Scene) == 0x250);
}
