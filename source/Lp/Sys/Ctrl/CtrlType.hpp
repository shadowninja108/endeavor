#pragma once

namespace Lp::Sys {

    enum CtrlType {
        CtrlType_cNone       = -1,
        CtrlType_cNormal     = 0x0,
        CtrlType_cDbgOrigin  = 0x1,
        CtrlType_cDbg        = 0x2,
        CtrlType_cDbgMix     = 0x3,
        CtrlType_cDbgNoInput = 0x4,
        CtrlType_End
    };

}