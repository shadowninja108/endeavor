#pragma once

#include "Texture.hpp"
#include "driver/NVNsampler.hpp"
#include "detail/SamplerObject.hpp"
#include "detail/CompSel.hpp"

namespace agl {
    struct TextureSampler {
        TextureData mTextureData;
        driver::NVNsampler_ mNvnSampler;
        const char* mDebugLabel;
        detail::SamplerObject mSamplerObj;
        detail::CompSel mCompSel;
        uint field_160;
        uchar field_164;
    };
    static_assert(sizeof(TextureSampler) == 0x1c8);
}