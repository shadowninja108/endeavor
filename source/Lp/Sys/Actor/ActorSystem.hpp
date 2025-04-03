#pragma once

#include <sead/thread/seadCriticalSection.h>
#include <sead/thread/seadReadWriteLock.h>
#include <sead/heap/seadDisposer.h>

#include "ActorReserveList.hpp"
#include "ActorCalculator.hpp"
#include "ActorPicker.hpp"
#include "Actor.hpp"
#include "Constants.hpp"

namespace Lp::Sys {
    struct RootActor;
    struct ActorSystem {
        uintptr_t field_8;
        sead::CriticalSection mCS;
        sead::ReadWriteLock mRWLock;

        SEAD_SINGLETON_DISPOSER(ActorSystem);

        public:

        enum class Step {
            Ctor      = 0x0,
            Init      = 0x1,
            Load      = 0x2,
            Enter     = 0x3,
            Reset     = 0x4,
            StartCalc = 0x5,
            Calc      = 0x6,
            Pause     = 0x7,
            Exit      = 0x8,
            Destroy   = 0x9,
        };

        struct InitArg {
            CalcBitfield mCalcBitfield;
            int mJobQueueSize;
            int field_8; /* Seems to never be read? */
        };

        RootActor* mRootActor;
        ActorReserveActivateList *mReserveActivateList1;
        ActorReserveActivateList *mReserveActivateList2;
        ActorReserveSleepList *mReserveSleepList1;
        ActorReserveSleepList *mReserveSleepList2;
        ActorReserveChangeTimingList *mReserveChangeTimingList1;
        ActorReserveChangeTimingList *mReserveChangeTimingList2;
        ActorReserveChangeJobPriorityList *mChangeJobPriorityList;
        ActorReserveRemoveList *mReserveRemoveList;
        ActorCalculator *mCalculator;
        CalcBitfield mCalcBitfield;
        int mCurCalcTiming;
        int mCurColCheckIdx;
        Step mStep;
        sead::CriticalSection mActorCS;
        ActorPicker* mPicker;
        bool field_1D0;

        virtual ~ActorSystem();
    };
}