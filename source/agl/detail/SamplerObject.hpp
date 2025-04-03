#pragma once

#include <common.hpp>

namespace agl::detail {
    struct SamplerObject {
        float field_0;
        float field_4;
        float field_8;
        float field_C;
        float mMinLod;
        float mMaxLod;
        float mLodBias;
        uchar mMagFilter;
        uchar field_1D;
        uchar field_1E;
        uchar field_1F;
        uchar field_20;
        uchar field_21;
        uchar mMaxAnisotropy;
        uchar mCompareMode;
    };
}