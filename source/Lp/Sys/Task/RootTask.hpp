#pragma once

#include <sead/framework/seadCalculateTask.h>
#include <sead/framework/seadTaskMgr.h>
#include "../Hio/IUseHioNode.hpp"

namespace Lp::Sys {
    struct RootTask : public sead::CalculateTask, public IUseHioNode {
        SEAD_TASK_SINGLETON(RootTask);

        static RootTask* spThis;
    };
}