#pragma once

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>
#include <time/seadTickSpan.h>
#include <time/seadTickTime.h>
#include <time/seadCalendarTime.h>
#include <prim/seadSafeString.hpp>

namespace sead {
    struct CuckooClock : public CalculateTask {
        SEAD_RTTI_OVERRIDE(CuckooClock, CalculateTask);
        SEAD_TASK_SINGLETON(CuckooClock);

        public:
        CalendarTime mLatestTime;
        TickTime mLatestTick;
        TickTime mLastCuckooTick;
        TickSpan mCuckooInterval;

        void initialize();
        void updateLatest_();
        void cuckoo_();
        void calcTime_(int*,int*,int*,int*) const;
        void getTimeString(BufferedSafeString*) const;
        void getUtcString_(BufferedSafeString*) const;

        virtual void calc() override;
    };
}