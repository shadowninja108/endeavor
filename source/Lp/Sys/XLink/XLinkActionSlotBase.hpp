#pragma once

#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/prim/seadSafeString.hpp>

namespace Lp::Sys {
    struct XLinkActionSlotBase {
        SEAD_RTTI_BASE(XLinkActionSlotBase);

        public:
        int mAnimCount;
        int mTriggerIndex; 

        virtual void reset();
        virtual bool tryChangeAction(sead::BufferedSafeString*);
        virtual void getActionName(sead::BufferedSafeString*, int) const;
        virtual int getFrame() const;
        virtual int getFrameOnChangeAction() const;
        virtual void calcActionName(sead::BufferedSafeString*, char const*) const;
    };
}