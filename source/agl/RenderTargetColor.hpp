#pragma once

#include <common.hpp>

#include <nvn.hpp>

#include "Texture.hpp"
#include "GPUMemAddrBase.hpp"

namespace agl {
    /* TODO: inherit from RenderTarget<RenderTargetColor> */
    struct RenderTargetColor {
        TextureData mTextureData;
        uchar field_180;
        uchar field_181;
        ushort field_182;
        int field_184;
        int field_188;
        GPUMemAddrBase field_190;
        NVNtextureView mTextureView;
    };
    static_assert(sizeof(RenderTargetColor) == 0x1D0);
}