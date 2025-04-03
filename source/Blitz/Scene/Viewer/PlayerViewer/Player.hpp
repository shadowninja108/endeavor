#pragma once

#include <Blitz/Cmn/Actor.hpp>

namespace PlayerViewer {
    struct Player : public Cmn::Actor {
        LP_ACTOR(Player, Cmn::Actor);
    };
}