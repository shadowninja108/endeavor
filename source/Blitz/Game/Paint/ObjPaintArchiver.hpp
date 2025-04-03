#pragma once

#include <common.hpp>

#include <agl/Texture.hpp>

#include <sead/prim/seadSafeString.hpp>
#include <sead/container/seadOffsetList.h>

namespace Game {
    struct ObjPaintArchiver {

        uintptr_t field_8;
        uchar field_10;

        struct Info {
            agl::TextureData mTexture;
            sead::FixedSafeString<64> mObjPaintName;
            sead::ListNode mListNode;
        };

        sead::OffsetList<Info> mInfos;

        virtual ~ObjPaintArchiver();
    };

    static_assert(sizeof(ObjPaintArchiver) == 0x30);
}