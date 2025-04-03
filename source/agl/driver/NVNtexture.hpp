#pragma once

#include <common.hpp>
#include <nvn.hpp>

namespace agl::driver {
    struct NVNtexture_ {
        NVNtexture mImpl;
        int mId;
        uchar field_c4;
    };
}