#pragma once

#include <common.hpp>

#include <sead/prim/seadSafeString.hpp>

namespace Lp::UI::Impl {
    struct Name {
        sead::SafeString mStr;
        uint mHash;
        ushort mStrLen;
        char field_16;
        char field_17;
    };
}