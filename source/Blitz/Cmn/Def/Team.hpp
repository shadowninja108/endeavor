#pragma once

#include <sead/prim/seadEnum.h>

namespace Cmn::Def {
    SEAD_ENUM(TeamBase, None, Team_Alpha, Team_Bravo, Neutral);

    struct Team : TeamBase {
        /* Why is this here...? */
        static inline TeamBase cNone = TeamBase::ValueType::None;
        static inline TeamBase cAlpha = TeamBase::ValueType::Team_Alpha;
        static inline TeamBase cBravo = TeamBase::ValueType::Team_Bravo;
        static inline TeamBase cNeutral = TeamBase::ValueType::Neutral;
    };
}