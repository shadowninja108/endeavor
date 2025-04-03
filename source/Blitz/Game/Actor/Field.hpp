#pragma once

#include <Lp/Sys/Model/ModelArc.hpp>

#include <sead/prim/seadSafeString.hpp>

#include "../../Cmn/Actor.hpp"
#include "../../Cmn/ActorDBData.hpp"
#include "../../Cmn/KCol/KDGndCol.hpp"

namespace Game {
    struct Field : public Cmn::Actor {
        LP_ACTOR(Field, Cmn::Actor);

        sead::FixedSafeString<256> mName;
        sead::FixedSafeString<256> field_3a0;
        sead::FixedSafeString<256> mFmdbName;
        sead::FixedSafeString<256> mXLinkName;
        Cmn::ActorDBData* mActorDBData;
        Lp::Sys::ModelArc* mModelArc;
        Cmn::KDGndCol::Manager* mKColMgr;
        Cmn::KDGndCol::BlockKCol* mKCol;
        /* ... */

        void initByMuData()
        void loadModelArc();
    };
}