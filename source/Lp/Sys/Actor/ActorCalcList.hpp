#pragma once

#include <sead/prim/seadSafeString.hpp>
#include <sead/mc/seadJobQueue.h>
#include <sead/mc/seadCoreInfo.h>
#include "Actor.hpp"
#include "ActorWorkderMgrKind.hpp"

namespace Lp::Sys {
    struct ActorCalcList {
        uintptr_t field_8;
        sead::FixedSizeJQ* mJobQueue;
        sead::Job0<Actor>** mJobsByCore[3]; /* TODO: probably a sead constant for this? */
        int mCalcTiming;
        sead::FixedSafeString<32> mDbgName;

        virtual ~ActorCalcList(); 
        void enqueueByActiveTree(bool randomizeJobsOnCore);
        void calc(sead::CoreIdMask, ActorWorkderMgrKind);
        void changeGranularity(int);
        void dumpConsoleCalcByParent(Actor const*);
        void dumpConsole();

    };
}