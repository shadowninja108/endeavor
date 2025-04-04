#pragma once

#include <types.h>
#include <sead/gfx/seadCamera.h>

namespace Lp::Sys {

    struct DbgCamera {
        enum FollowType {
            FollowType_Unk,
        };
        void follow(sead::Vector3<float> const&,bool,bool,int,FollowType);
        void calc(bool isFollow);
        u8 _0[0x18];
        sead::LookAtCamera mCamera;
    };

}