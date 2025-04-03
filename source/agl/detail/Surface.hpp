#pragma once

#include <common.hpp>

#include "CompSel.hpp" 

namespace agl::detail {
    struct Surface {
        ushort mFormat;
        ushort mType;
        uchar mAA;
        uchar mNumMips;
        uchar mAttribute;
        uchar mPixelByteSize;
        ushort mWidth;
        ushort mHeight;
        ushort mDepth;
        uint mAlignment;
        uint mImageSize;
        uintptr_t mImagePtr;
        uint mMipSize;
        uintptr_t mMipPtr;
        uint mMipByteSizeByLevel[14];
        uchar field_68;
        uchar field_69;
        uchar mAttribute2;
        uchar field_6B;
        uint mStride;
        CompSel mCompSel;
        uint field_74;
    };
}