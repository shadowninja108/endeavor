#pragma once

#include <sead/prim/seadDelegate.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/prim/seadRuntimeTypeInfo.h>

namespace Cmn {
    template<typename PrimitiveT, typename Wrapped>
    struct DbgMenuItemEvent : public Wrapped {
        using SelfType = DbgMenuItemEvent<PrimitiveT, Wrapped>;
        SEAD_RTTI_OVERRIDE(SelfType, Wrapped);

        public:
        PrimitiveT mValue;
        sead::AnyDelegate1<PrimitiveT> mDelegate;

        DbgMenuItemEvent(sead::SafeString const&, PrimitiveT, void(*)(PrimitiveT));
        
        template<typename Class>
        DbgMenuItemEvent(sead::SafeString const&, PrimitiveT *,void (Class::*)(PrimitiveT));
    };
}