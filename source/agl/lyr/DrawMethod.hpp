#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/prim/seadDelegate.h>

namespace agl::lyr {
    struct RenderInfo;

    struct DrawMethod : sead::IDisposer {
        sead::SafeString mName;
        int field_30;
        int field_34;
        int field_38;
        sead::Delegate1<DrawMethod, RenderInfo const&> mDelegate;
    };
    static_assert(sizeof(DrawMethod) == 0x60, "");
}