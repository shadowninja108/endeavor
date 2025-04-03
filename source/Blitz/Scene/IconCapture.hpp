#pragma once

#include <common.hpp>

#include <sead/heap/seadHeap.h>

#include "Cmn/SceneBase.hpp"

namespace IconCapture {
    struct Scene : public Cmn::SceneBase {
        SEAD_RTTI_OVERRIDE(Scene, Cmn::SceneBase);
        
        ulong padding[(0x146CC8 - sizeof(Cmn::SceneBase))/sizeof(ulong)];

        Scene(sead::Heap*);
    };
    static_assert(sizeof(Scene) == 0x146CC8, "");
}