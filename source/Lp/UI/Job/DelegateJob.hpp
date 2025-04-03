#pragma once

#include <sead/prim/seadDelegate.h>

#include "Job.hpp"

namespace Lp::UI {
    struct PageBase;

    struct DelegateJob : public Job {
        /* TODO: ? */
        sead::Delegate<PageBase> mDelegate;
    };
    static_assert(sizeof(DelegateJob) == 0x98);
}