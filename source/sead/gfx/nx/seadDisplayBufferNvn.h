#pragma once

#include <gfx/seadDisplayBuffer.h>
#include <math/seadVector.hpp>
#include <nvn/nvn.hpp>

namespace sead {
    struct DisplayBufferNvn : public DisplayBuffer {
        SEAD_RTTI_OVERRIDE(DisplayBufferNvn, DisplayBuffer);

        public:
        Vector2f* mResolution;
        NVNwindow* mWindow;
        NVNsync* mSync;
        int mTextureIndex;
        NVNtexture* mBufferTextures[3];
        NVNdevice* mDevice;
        uchar mPresentInterval;
        uchar mBufferCount;
        bool mPendingWindowCrop;
        uint mCropX;
        uint mCropY;
        uint mCropWidth;
        uint mCropHeight;
    };
}