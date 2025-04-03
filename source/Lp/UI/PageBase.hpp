#pragma once

#include <common.hpp>

#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/thread/seadReadWriteLock.h>

#include "Impl/Name.hpp"
#include "Impl/DrawSightArg.hpp"
#include "Input/InputContext.hpp"
#include "Job/Job.hpp"
#include "Job/DelegateJob.hpp"

namespace Lp::UI {
    struct PageHolder;

    struct PageBase {
        SEAD_RTTI_BASE(PageBase);

        uintptr_t field_8;
        uintptr_t field_10;
        uintptr_t field_18;
        uintptr_t field_20;
        sead::ListNode mListNode;
        Impl::Name field_30;
        PageHolder* mHolder;
        int mState; /* TODO: */
        uint mPauseFlags;
        char field_60;
        int field_64;
        PageBase* mParentPage;
        sead::OffsetList<PageBase> mChildPages;
        DelegateJob mPostCalcJob;
        sead::ReadWriteLock mChildPagesRwLock;

        virtual ~PageBase();
        virtual uintptr_t getClassInfo();
        virtual void endInitializeImpl();
        virtual void finalizeImpl();
        virtual void wakeImpl();
        virtual void sleepImpl();
        virtual void priorManipulateImpl(InputContext*, bool);
        virtual void preCalcImpl();
        virtual void postCalcImpl();
        virtual void updateBindingImpl();
        virtual void chainPostCalcImpl(Job*, bool);
        virtual void drawLayoutImpl(Impl::DrawSightArg*);
        virtual void onPreWake();
        virtual void onPostWake();
        virtual void onPreSleep();
        virtual void onPostSleep();
        virtual void onPreCalc();
        virtual void onPostCalc();
    };
    static_assert(sizeof(PageBase) == 0x1E8);
}