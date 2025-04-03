#pragma once

#include <sead/prim/seadSafeString.hpp>

namespace Lp::Utl  {
    struct Meta {
        sead::FixedSafeString<256> mData;
    };
}