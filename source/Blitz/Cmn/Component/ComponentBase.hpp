#pragma once

#include <sead/prim/seadRuntimeTypeInfo.h>

namespace Cmn {
    struct ComponentBase : public sead::RuntimeTypeInfo::Interface {

        virtual ~ComponentBase();
    };
}