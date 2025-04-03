#pragma once

#include <sead/container/seadOffsetList.h>

#include "MuElement.hpp"
#include "MuObj.hpp"

namespace Cmn {
    struct MuObjs : public MuElement {
        SEAD_RTTI_OVERRIDE(MuObjs, MuElement);
        public:
        
        sead::OffsetList<MuObj> mList;
    };
}