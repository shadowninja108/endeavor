#pragma once

#include <sead/container/seadSafeArray.h>
#include "../../Utl/BigBitsT.hpp"
#include "../Hio/IUseHioNode.hpp"
#include "ActorCalcList.hpp"
#include "Constants.hpp"

namespace Lp::Sys {
    struct ActorCalculator : public Lp::Sys::IUseHioNode {
        uintptr_t field_8;
        sead::SafeArray<ActorCalcList*, s_ActorSystem_MaxCalcList> mCalcLists;
        CalcBitfield mCalcBitfield;
        bool mRandomizeJobsOnCores;

        virtual ~ActorCalculator();

        ActorCalculator(CalcBitfield const&, int, int);

        void tellChangeActiveTree(CalcBitfield const&);
        sead::SafeString const* getDbgName(int);
        void setDbgName(int, sead::SafeString const&);
        void calc(int, sead::CoreIdMask, ActorWorkderMgrKind);
        void changeGranularity(int, int);
        void dumpCalcListConsole(int);
    };
}