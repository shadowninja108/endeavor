#pragma once

#include <sead/prim/seadSafeString.hpp>

#include <Lp/Sys/Model/ModelArc.hpp>

namespace Cmn {
    struct CameraAnimResource {
        void loadImpl(Lp::Sys::ModelArc*, sead::SafeString const&, sead::SafeString const*, int, bool);
    };
}