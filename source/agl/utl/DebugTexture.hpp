#pragma once

#include <sead/container/seadOffsetList.h>
#include <sead/prim/seadSafeString.hpp>

#include "../Texture.hpp"

namespace agl::utl {
    struct DebugTexture {
        enum class Type {};

        sead::ListNode mListNode;
        uintptr_t field_18;
        sead::OffsetList<DebugTexture>* mParentList;
        sead::FixedSafeString<32> field_28;
        const TextureData* mData;
        bool field_68;
        bool field_69;
        bool field_6A;
        Type mType;
        float field_70;
        float field_74;
        char field_78;
        char field_79;

        virtual ~DebugTexture();
    };
    static_assert(sizeof(DebugTexture) == 0x80);
}