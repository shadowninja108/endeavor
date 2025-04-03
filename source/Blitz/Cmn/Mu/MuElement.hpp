#pragma once

#include <Lp/Utl/Byaml/Iter/ByamlIter.hpp>

#include <sead/container/seadRingBuffer.h>
#include <sead/container/seadBuffer.h>
#include <sead/math/seadMatrix.hpp>
#include <sead/math/seadMatrix.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/prim/seadRuntimeTypeInfo.h>

#include "../Def/Team.hpp"

#include "MuLayer.hpp"

namespace Cmn {
    struct MuElement : public sead::RuntimeTypeInfo::Interface {
        SEAD_RTTI_BASE(MuElement);
        public:

        struct LinkInfo {
            sead::FixedRingBuffer<256> mDefinitionName;
            sead::FixedRingBuffer<256> mDestUnitId;
        };

        MuElement* mParent;
        Lp::Utl::ByamlIter* mByaml;
        sead::FixedSafeString<32> mId;
        sead::FixedSafeString<64> mUnitConfigName;
        sead::BaseMtx33<float> mMtx;
        sead::Vector3f mPos;
        sead::Vector3f mScale;
        sead::Vector3f mRotate;
        int mLinkInfoCount;
        sead::FixedRingBuffer<LinkInfo, 32> mLinkSrcs;
        sead::Buffer<LinkInfo> mLinkDsts;
        LinkInfo mLinkDstsBuffer[32];
        MuLayer mLayer;

        virtual ~MuElement();
        virtual void init(Lp::Utl::ByamlIter const&, sead::SafeString const&);
        virtual const sead::Vector3f* getPos() const;
    };
}