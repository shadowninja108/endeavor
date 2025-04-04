#pragma once

#include <types.h>

namespace Game {
    struct FilmingSupporter;
}
extern "C" void _ZN4Game16FilmingSupporterC2Ev(Game::FilmingSupporter*);
namespace Game {
    struct FilmingSupporter {
        enum AimMode{
            AimMode_None,
            AimMode_FixedAim,
            AimMode_Unk,
        };
        u8 _0[0x34];
        int mPlayerId;
        u8 _38[0x98 - 0x38];

        inline FilmingSupporter(){
            _ZN4Game16FilmingSupporterC2Ev(this);
        };
        void calc();
        void enter();
        void changeMode_(AimMode aimMode);
        void calcFixedAim_();
    };
}