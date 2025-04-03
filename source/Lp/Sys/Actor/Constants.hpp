#pragma once

#include <common.hpp>

#include "../../Utl/BigBitsT.hpp"

namespace Lp::Sys {
    static constexpr size_t s_ActorSystem_MaxCalcList = 32;
    
    using CalcBitfield = Utl::BigBitsT<s_ActorSystem_MaxCalcList>;
}