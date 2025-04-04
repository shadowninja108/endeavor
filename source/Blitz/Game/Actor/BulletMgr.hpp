#pragma once

#include <types.h>

#include "../../Cmn/Actor.hpp"

namespace Game {
    class BulletMgr : public Cmn::Actor  {
        LP_ACTOR(BulletMgr, Cmn::Actor);

        public:
        void createActors();
    };
}
