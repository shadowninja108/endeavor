#pragma once

#include "Obj.hpp"
#include "../../Cmn/Def/ResetType.hpp"

namespace Game {
    struct Lift : public Obj {
        LP_ACTOR(Lift, Obj);
        
        void load_();
        void reset_(Cmn::Def::ResetType type);
    };
}