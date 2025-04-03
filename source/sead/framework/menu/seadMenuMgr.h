#pragma once

#include <sead/framework/menu/seadDebugMenu.h>
#include <sead/framework/seadTaskParameter.h>
#include <framework/seadTask.h>
#include <gfx/seadTextWriter.h>
#include <gfx/seadViewport.h>
#include <prim/seadBitFlag.h>
#include <time/seadCalendarTime.h>

namespace sead {
    struct SeadMenuMgr : public Task {
        SEAD_RTTI_OVERRIDE(SeadMenuMgr, Task);

        public:
        struct SeadMenuParameter : public TaskParameter {
            SEAD_RTTI_OVERRIDE(SeadMenuParameter, TaskParameter);
            public:
            int mHeapLimitNum;
            int mThreadLimitNum;
            int mMethodTreeLimitNum;
            int mRootLimitNum;
        };

        char field_200;
        Viewport field_208;
        DebugMenu* mMenu;
        BitFlag32 mVisibleHoldMask;
        BitFlag32 mVisibleTriggerMask;
        BitFlag32 mReportHoldMask;
        BitFlag32 mReportTriggerMask;
        bool mDoDraw;
        bool mDoCalc;
        /* TODO: */
        uintptr_t mRootPage;
        uintptr_t mSystemInformationPage;
        uintptr_t mSystemConfigPage;
        uintptr_t mThreadViewPage;
        uintptr_t mHeapViewPage;
        uintptr_t mHeapDetailPage;
        int mHeapLimitNum;
        int mThreadLimitNum;
        int mMethodTreeLimitNum;
        int mRootLimitNum;
        CalendarTime field_298;
    };
}