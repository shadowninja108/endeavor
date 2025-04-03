#pragma once

#include "PaintTexture.hpp"

#include <common.hpp>
#include <sead/heap/seadDisposer.h>

namespace Game {
    struct PaintMgr {
        SEAD_SINGLETON_DISPOSER(PaintMgr);
        
        private: 
        uintptr_t Get() const {
            return reinterpret_cast<uintptr_t>(this);
        }

        public:
        PaintTexture* GetPaintTexture() const {
            return reinterpret_cast<PaintTexture*>(Get() + 0xC2F8);
        }
    };
}