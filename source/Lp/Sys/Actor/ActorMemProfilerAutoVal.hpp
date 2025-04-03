#pragma once

#include <sead/prim/seadSafeString.hpp>

#include "ActorMemProfiler.hpp"

namespace Lp::Sys {
    struct Actor;
    struct ActorMemProfilerAutoVal {

        sead::FixedSafeString<32> mClassName;
        ActorMemProfiler::Func mFunc;

        ActorMemProfilerAutoVal(Actor const*, ActorMemProfiler::Func);
        ActorMemProfilerAutoVal(sead::SafeString const&, ActorMemProfiler::Func);
        virtual ~ActorMemProfilerAutoVal();
    };
}