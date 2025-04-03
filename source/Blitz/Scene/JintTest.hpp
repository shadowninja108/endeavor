#pragma once

#include <common.hpp>

#include <sead/heap/seadHeap.h>
#include <sead/gfx/seadCamera.h>

#include "Cmn/SceneBase.hpp"

namespace JintTest {
    struct Scene : Cmn::SceneBase {
        SEAD_RTTI_OVERRIDE(Scene, Cmn::SceneBase);
        
        sead::LookAtCamera* m3DCam;

        Scene(sead::Heap*);
    };
    static_assert(sizeof(Scene) == 0x390, "");
}