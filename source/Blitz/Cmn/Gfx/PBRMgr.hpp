#pragma once

#include <lib.hpp>

#include <sead/heap/seadDisposer.h>
#include <sead/heap/seadHeap.h>

namespace Cmn {
    struct PBRMgr {
        SEAD_SINGLETON_DISPOSER(PBRMgr);


        public:
        void setDebugDrawEnvMap(bool);
        void load(sead::Heap*);

        /* Hack. */
        inline uintptr_t& GetViewerEnvMapBinRef() {
            return *reinterpret_cast<uintptr_t*>(
                reinterpret_cast<uintptr_t>(this) + 0x9718
            );
        }
    };
}