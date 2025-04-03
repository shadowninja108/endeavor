#pragma once

#include <common.hpp>

#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/container/seadOffsetList.h>

#include "Impl/LayoutSight.hpp"
#include "Impl/Name.hpp"

namespace Lp::UI {
    struct Page;
    struct Control {
        SEAD_RTTI_BASE(Control);

        struct List {
            sead::OffsetList<Control> mList;
        };

        sead::ListNode mListNode;
        Impl::Name mName;
        Control* mParent;
        List mChildren;
        Page* mParentPage;
        Impl::LayoutSight* mLayoutSight;
        

        virtual ~Control();
        virtual uintptr_t getClassInfo() const;
        virtual void onBoundSight();
        virtual void onPreWake();
        virtual void onPostWake();
        virtual void onPreSleep();
        virtual void onPostSleep();
        virtual void onPreCalc();
        virtual void onPostCalc();
    };
}