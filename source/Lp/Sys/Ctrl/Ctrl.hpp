#pragma once

#include "CtrlData.hpp"
#include "CtrlData200Hz.hpp"
#include "CtrlType.hpp"

#include <sead/prim/seadSafeString.hpp>
#include <sead/controller/seadController.h>

namespace Lp::Sys {

    struct Ctrl {

        uintptr_t field_8;
        CtrlData mData[2];
        int mDataNum;
        uint field_154;
        uint mNumSysData;
        CtrlData200Hz m200HzData[16];
        int field_BDC;
        char field_BE0;
        char field_BE1;
        CtrlType mCtrlType;
        int field_BE8;
        sead::FixedSafeString<32> mCtrlTypeString;
        sead::Controller* mSeadDevice;
        int field_C30;
        int field_C38;

        /* TODO: */
        virtual ~Ctrl();
    };
    static_assert(sizeof(Ctrl) == 0xC38);

}