#pragma once

#include <common.hpp>
#include <sead/prim/seadLongBitFlag.h>

namespace Lp::Utl {
    template<size_t BitCount>
    struct BigBitsT : sead::LongBitFlag<BitCount> {
        static BigBitsT<BitCount> zero;
    };
}