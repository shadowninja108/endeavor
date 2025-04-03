#pragma once

#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/heap/seadDisposer.h>
#include <sead/prim/seadSafeString.hpp>

#include <Lp/UI/PageHolder.hpp>

namespace Cui {
    struct PageHandler : sead::IDisposer {
        SEAD_RTTI_BASE(PageHandler);

        sead::ListNode mListNode;
        Lp::UI::PageHolder* mPageHolderPtr;
        Lp::UI::PageHolder mPageHolder;
        int mPauseType; /* TODO */
        int mLayerIdx;
        sead::FixedSafeString<64> mPageName;

        virtual void createPage(); 
    };
    static_assert(sizeof(PageHandler) == 0x130);
}