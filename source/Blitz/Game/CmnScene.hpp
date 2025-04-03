#pragma once

#include <common.hpp>

#include <sead/heap/seadHeap.h>

namespace Game {
    struct CmnScene {
        ulong padding[0x390/sizeof(ulong)];

        CmnScene(sead::Heap*);
    };
    static_assert(sizeof(CmnScene) == 0x390);
}
