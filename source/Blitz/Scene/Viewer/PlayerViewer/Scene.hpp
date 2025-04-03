#pragma once

#include <common.hpp>

#include <sead/heap/seadHeap.h>

#include "Cmn/SceneBase.hpp"

#include "Player.hpp"

namespace PlayerViewer {
    struct Scene : public Cmn::SceneBase {
        SEAD_RTTI_OVERRIDE(Scene, Cmn::SceneBase);
        
        ulong padding[(0x4A0 - sizeof(Cmn::SceneBase))/sizeof(ulong)];

        Scene(sead::Heap*);
    };
    static_assert(sizeof(Scene) == 0x4A0, "");
}