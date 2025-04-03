#pragma once

#include <common.hpp>
#include <sead/math/seadVector.hpp>

namespace Lp::Sys {

    struct CtrlData {

        enum ButtonBitfield {
            Button_A = 0x1,
            Button_B = 0x2,
            Button_ZL = 0x4,
            Button_X = 0x8,
            Button_Y = 0x10,
            Button_ZR = 0x20,
            Button_RStick = 0x40,
            Button_LStick = 0x80,
            Button_H = 0x100,
            Button_Minus = 0x200,
            Button_Plus = 0x400,
            Button_Plus2 = 0x800,
            Button_Minus2 = 0x1000,
            Button_L = 0x2000,
            Button_R = 0x4000,
            Button_Unk2 = 0x8000,
            Button_Dpad_Up = 0x10000,
            Button_Dpad_Down = 0x20000,
            Button_Dpad_Left = 0x40000,
            Button_Dpad_Right = 0x80000,
        };

        ButtonBitfield mHold;
        uint mButtonTrigLengths[32];
        ButtonBitfield mTrig;
        ButtonBitfield mReleased;
        ButtonBitfield mRepeat;
        sead::Vector2f mSticks[2];
    };
}