#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/heap/seadExpHeap.h>

#include <agl/Texture.hpp>
#include <agl/utl/DebugTexturePage.hpp>

#include "ObjPaintArchiver.hpp"

namespace Game {
    struct PaintTextureArchiver {
        uintptr_t field_8;
        SEAD_SINGLETON_DISPOSER(PaintTextureArchiver);
        public:
        struct WorldEntry {
            agl::TextureData* mArchiveTex;
            ObjPaintArchiver mArchiveObjs;
            bool mUsed;
            bool mAllocated;
        };

        WorldEntry mWorldArchives[5]; /* Probably a constant for the world count? */
        sead::ExpHeap* mStaticPaintTextureHeap;
        agl::utl::DebugTexturePage mDbgTexturePage;

        virtual ~PaintTextureArchiver();
    };
    static_assert(sizeof(PaintTextureArchiver) == 0x3B8);
}