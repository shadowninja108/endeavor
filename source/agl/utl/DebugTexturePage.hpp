#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/hostio/seadHostIONode.h>
#include <sead/hostio/seadHostIOReflexible.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/container/seadBuffer.h>
#include <sead/container/seadOffsetList.h>

#include "DebugTexture.hpp"

namespace agl::utl {
    struct DebugTexturePage : sead::IDisposer, sead::hostio::Node {
        struct Context {
            int field_0;
            sead::OffsetList<DebugTexture> mTextures;
            float field_20;
            int field_24;
            float field_28;
            int field_2C;
            int field_30;
            int field_34;
            float field_38;
            const DebugTexturePage* mPage;
        };
        static_assert(sizeof(Context) == 0x48);
        
        struct DrawOption {
            char field_0;
            char field_1;
            char field_2;
            int field_4;
            int field_8;
        };
        static_assert(sizeof(DrawOption) == 0xC);

        sead::ListNode mListNode;
        uintptr_t field_38;
        uintptr_t field_40;
        sead::FixedSafeString<128> field_48;
        sead::FixedSafeString<128> field_E0;
        sead::FixedSafeString<128> field_178;
        bool mActive;
        int field_214;
        sead::Buffer<Context> mContexts;
        DrawOption mDrawOption;
        sead::hostio::Reflexible* mReflexlible;
    };
    static_assert(sizeof(DebugTexturePage) == 0x240);
}