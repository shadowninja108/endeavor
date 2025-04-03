#pragma once

#include <sead/container/seadListImpl.h>
#include <sead/prim/seadSafeString.hpp>

#include "../Impl/Name.hpp"
#include "TotalValueConverter.hpp"

namespace Lp::UI {
    struct TypeInfo;
    struct ValueConverter {
        sead::ListNode mListNode;
        const TypeInfo* field_18;
        const TypeInfo* field_20; 
        Impl::Name field_28;

        virtual ~ValueConverter();
        virtual void totalConvertImpl(void*, void const*, TotalValueConverter const&);
        virtual void convert(void*, void const*);
    };
}