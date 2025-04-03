#pragma once

#include "GPUMemAddrBase.hpp"
#include "detail/Surface.hpp"
#include "driver/NVNtexture.hpp"

namespace agl {
    struct TextureData {
        /* TODO: this is prob VoidAddr? */
        GPUMemAddrBase mImagePtr;
        GPUMemAddrBase mMipPtr;
        detail::Surface mSurface;
        ushort mTextureFormat;
        uchar field_56;
        driver::NVNtexture_ mNVNTexture;
        char* mDebugLabel;
    };
}