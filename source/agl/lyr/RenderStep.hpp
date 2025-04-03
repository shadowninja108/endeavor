#pragma once

#include <sead/hostio/seadHostIONode.h>
#include <sead/container/seadPtrArray.h>

#include "DrawMethod.hpp"

namespace agl::lyr {
    struct RenderStep : sead::hostio::Reflexible {
        sead::FixedPtrArray<DrawMethod, 256> mMethods;
        int field_818;

        RenderStep();
        void calc();
        void removeByObject(void const*);
        void remove(DrawMethod const*);
        void clear();
    };
}