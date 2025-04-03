#pragma once

#include <sead/prim/seadSafeString.hpp>
#include <sead/container/seadStrTreeMap.h>

#include "MuObj.hpp"

namespace Cmn {
    struct MuData {
        using MuObjTree = sead::StrTreeMap<MuObj*, 128>;
        using MuObjsTree = sead::StrTreeMap<MuObjs*, 128>;

        /* Probably some FixedStrTreeMap? */
        MuObjTree mMuObjTree;
        MuObjTree::Node mMuObjTreeBuffer[0x600];
        MuObjsTree mMuObjsTree;
        MuObjsTree::Node mMuObjsTreeBuffer[0x400];

        MuData(sead::SafeString const&);
    };
}