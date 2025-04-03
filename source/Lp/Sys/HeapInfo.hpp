#pragma once

#include <common.hpp>

namespace Lp::Sys {
    struct HeapInfo {
        size_t mSysSize;
        size_t mGfxSize;
        size_t mResSize;
        size_t mSndSize;
        size_t mSceneSize;
        size_t field_28;

        static HeapInfo* spInfo;
    };
}