#pragma once

#include <sead/framework/nx/seadGameFrameworkNx.h>

namespace Lp::Sys {
    struct Framework : public sead::GameFrameworkNx {
        SEAD_RTTI_OVERRIDE(Framework, sead::GameFrameworkNx);

        ResetEvent mResetEvent;
        sead::TickSpan mGpuTick;
        sead::TickTime mProcFrameTick;

        static Framework* spInstance;
    };
}