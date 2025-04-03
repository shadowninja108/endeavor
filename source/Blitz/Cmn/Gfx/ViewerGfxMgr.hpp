#pragma once

#include <sead/prim/seadRuntimeTypeInfo.h>

#include "GfxMgr.hpp"
#include "ViewerEnvChanger.hpp"

namespace Cmn {
    struct ViewerGfxMgr : public GfxMgr {
        SEAD_RTTI_OVERRIDE(ViewerGfxMgr, GfxMgr);
        
        ViewerEnvChanger* mEnvChanger;
    };
    static_assert(sizeof(ViewerGfxMgr) == 0x320);
}