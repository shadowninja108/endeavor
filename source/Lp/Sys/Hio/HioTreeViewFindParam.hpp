#pragma once

#include "IUseHioNode.hpp"

namespace Lp::Sys {
    struct HioTreeViewFindParam {
        const char* mParentName;
        IUseHioNode* mObj;
        const char* mViewNode;
    };
}