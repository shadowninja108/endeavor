#pragma once

#include <sead/prim/seadSafeString.hpp>

namespace Cmn {
    struct ActorDBData {
        int field_0;
        int mIndex;
        sead::FixedSafeString<64> mName;
        sead::FixedSafeString<64> mClassName;
        sead::FixedSafeString<64> mResName;
        sead::FixedSafeString<64> mFmdbName;
        sead::FixedSafeString<64> mJmpName;
        sead::FixedSafeString<64> mLinkUserName;
        sead::FixedSafeString<64> mParamsFileBaseName;
    };
}