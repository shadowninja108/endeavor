#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/container/seadOffsetList.h>
#include <sead/heap/seadHeap.h>
#include <sead/heap/seadExpHeap.h>

#include "PageBase.hpp"

#include "Impl/DualHeapAdapter.hpp"
#include "Impl/LayoutResourceMgr.hpp"
#include "Impl/Name.hpp"
#include "Impl/LayoutResourceAccessorHolder.hpp"

namespace Lp::UI {
    struct PageHolder : public sead::IDisposer {
        struct HeapSet {
            sead::ListNode mListNode;
            sead::ExpHeap* mHeap;
            Impl::DualHeapAdapter* mDualHeapAdapter;
            Impl::LayoutResourceMgr mLytResMgr;
        };
        
        uintptr_t field_20;
        uintptr_t field_28;
        Impl::Name field_30;
        sead::Heap* field_48;
        sead::OffsetList<HeapSet> mHeapSetList;
        HeapSet* mRootHeapSet;
        bool field_70;
        sead::OffsetList<PageBase> mChildPages;
        Impl::LayoutResourceAccessorHolder* field_90;
    };
}