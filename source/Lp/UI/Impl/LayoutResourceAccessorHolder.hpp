#pragma once

#include <sead/thread/seadCriticalSection.h>
#include <sead/container/seadOffsetList.h>

namespace Lp::UI::Impl {
    struct LayoutResourceAccessor;
    struct LayoutResourceAccessorHolder {
        bool field_0;
        /* TODO: what are the purposes for each? */
        sead::OffsetList<LayoutResourceAccessor> mList1;
        sead::OffsetList<LayoutResourceAccessor> mList2;
        LayoutResourceAccessor* mTemporaryAccessor;
        sead::CriticalSection mCS;
    };
}