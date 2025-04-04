#pragma once

#include "../../Cmn/Actor.hpp"
#include "../../Cmn/KCol/KDGndCol.hpp"

namespace Game {
    struct Obj : public Cmn::Actor {
        LP_ACTOR(Obj, Cmn::Actor);
        Cmn::KDGndCol::BlockKCol* getBlock(int idx);
        void createModelAndAnim_();
    };
}