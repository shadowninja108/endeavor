#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/heap/seadHeap.h>
#include <sead/prim/seadSafeString.hpp>

#include "../DrawContext.hpp"
#include "../Texture.hpp"
#include "../TextureDataSerializerTGA.hpp"

namespace agl::utl {
    struct ScreenShotMgr {
        SEAD_SINGLETON_DISPOSER(ScreenShotMgr);
        public:

        sead::Heap* mHeap;

        virtual ~ScreenShotMgr();
        bool captureToFile_(agl::DrawContext*, agl::TextureData const*, agl::TextureDataSerializerTGA::TGAFormat, sead::SafeString const&, sead::Heap*) const;
    };
}