#pragma once

#include <types.h>
#include "DbgCamera.hpp"
namespace Lp::Sys {

    struct DbgCameraMgr {
        static DbgCameraMgr* sInstance;
        u8 _0[0x4B0];
        int mLayerNum;
        int _4B4;
        DbgCamera** mLayerCameras;
    };

}