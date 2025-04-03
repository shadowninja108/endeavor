#pragma once

#include "LayoutResourceAccessorHolder.hpp"
#include "DualHeapAdapter.hpp"

namespace Lp::UI::Impl {
    struct LayoutResourceMgr {
        /* TODO: */
        struct Entry;

        LayoutResourceAccessorHolder* mLytResAccessorHolder;
        int field_8;
        sead::OffsetList<Entry> mEntries;
        DualHeapAdapter* mHeapAdapter;
    };
}