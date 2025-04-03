#pragma once

#include "Ctrl.hpp"

namespace Lp::Sys {
    struct DbgMixCtrl : public Ctrl {
        uint mBitfield;
    };
}