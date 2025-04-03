#pragma once

#include <sead/container/seadListImpl.h>
#include "MuElement.hpp"

namespace Cmn {
    struct Obj;
    struct MuObj : public MuElement {
        SEAD_RTTI_OVERRIDE(MuObj, MuElement);
        public:
        Def::Team mTeam;
        Obj* mActor;
        sead::ListNode mListNode;

        virtual ~MuObj() override;
        virtual void init(Lp::Utl::ByamlIter const&, sead::SafeString const&) override;
    };
}