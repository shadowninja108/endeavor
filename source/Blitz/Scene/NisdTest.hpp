#pragma once

#include <common.hpp>

#include <sead/heap/seadHeap.h>

#include "Cmn/SceneBase.hpp"

namespace NisdTest {
    struct Scene : public Cmn::SceneBase {
        SEAD_RTTI_OVERRIDE(Scene, Cmn::SceneBase);
        
        ulong padding[(0x708 - sizeof(Cmn::SceneBase))/sizeof(ulong)];

        Scene(sead::Heap*);
    };
    static_assert(sizeof(Scene) == 0x708, "");
}